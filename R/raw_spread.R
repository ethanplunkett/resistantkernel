#' Interface for the C++ spread code - mainly for internal use
#' 
#' `raw_spread()` takes a spread value, the focal cell coordinates, and a
#' resistance matrix (all values >= 1); executes a resistant spread; and
#' returns the final snapshot of the spread as a matrix.
#' 
#' `raw_spread()` calculates the functional proximity of each cell to the
#' focal cell. With the proximity highest at the focal cell where it is 
#' equal to the `spread_value` and diminishing with distance from the focal
#' cell (based on the resistance of intervening cells).  The functional 
#' proximity thus is zero for cells with a functional distance greater than
#' `spread_value` from the focal cell, regardless of how much greater. In 
#' practice larger spread values allow calculation of a larger functional
#' distances but requires more processor time. 
#' #' 
#' @param x the resistance matrix, all values must be >= 1
#' @param spread_value the initial bank account for the spread, which is
#' depleted based on the resistance of each cell as the spread progresses.
#' @param row the focal row of the spread
#' @param col the focal column of the spread
#' @return A matrix with the same dimensions as `x` the values of which
#' represent the functional proximity to the focal cell.  They range from
#' `spread_value` (at the focal cell) to zero for cells greater than
#' `spread_value` away from the focal cell.
#' @author Ethan Plunkett
#' @seealso [spread]
#' @examples
#'
#' # Create (minimally resistant) test matrix 
#' res <- matrix(1, 5, 5)
#' res
#' raw_spread(res, 10, 3, 3)
#' 
#' # Add two higher resistance bands
#' res[2, ]  <- 5
#' res[,2] <- 5
#' res
#' raw_spread(res, 10, 3, 3)
#' 
#' @export 
raw_spread <- function(x, spread_value, row, col){
	x<-as.matrix(x)  # so dim call works properly
	row <- as.integer(row)
	col <- as.integer(col)
	rows <- as.integer(dim(x)[1])
	columns <- as.integer(dim(x)[2])
	spread_value <- as.double(spread_value)	
	x<-as.double(as.vector(t(x))) #convert to vector for passing to C
	
	error.msg <- as.integer(0)
	
	result<-.C("rspread", 
			as.double(spread_value), 
			as.integer(row), 
			as.integer(col), 
			as.integer(rows), 
			as.integer(columns),
			as.double(x),
			as.integer(error.msg),
			PACKAGE="resistantkernel")
	if (error.msg < 0) stop("spread function in dll/so reported error")
	
	matrix(result[[6]],rows, columns, byrow=TRUE)
	} # End r.spread function Definition


