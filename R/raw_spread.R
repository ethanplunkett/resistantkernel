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
#' 
#' @param x the resistance matrix, all values must be >= 1
#' @param spread_value the initial bank account for the spread, which is
#' depleted based on the resistance of each cell as the spread progresses.
#' @param row the focal row of the spread
#' @param col the focal column of the spread
#' @param square if `TRUE` then the diagonal cells will be considered to be one
#' cell length away from the center and the spread will tend to be square.  
#' The default of `FALSE` uses a diagonal length of 1.4 cells and spreads 
#' tend to be octagonal.
#' @param symmetrical If `TRUE` then the average resistance of the source 
#' and neighboring destination cell is used to represent the cost of stepping
#' to a neighboring cell. If `FALSE` then the destination cell is used to 
#' represent the cost of the step.  
#' The original 2009 algorithm is equivalent to `FALSE`.
#' If `TRUE` then the cost difference between a source and any 
#' (not necessarily adjacent) destination  will be the same as the cost 
#' distance from that destination to the source, 
#' and both will include half the cost of traversing the source and destination
#' cells. 
#' If `FALSE` that is not guaranteed as the source cell cost is not included
#' and the full destination cell cost is. 
#' @return A matrix with the same dimensions as `x` the values of which
#' represent the functional proximity to the focal cell.  They range from
#' `spread_value` (at the focal cell) to zero for cells greater than
#' `spread_value` (cost) away from the focal cell.
#' @seealso [spread]
#' @examples
#'
#' # Create (minimally resistant) test matrix 
#' a <- matrix(1, 5, 5)
#' a
#' raw_spread(a, 10, 3, 3, FALSE, TRUE)
#' 
#' # Add two higher resistance bands
#' a[2, ]  <- 5
#' a[,2] <- 5
#' a
#' # Average of source and destination resistance used with each step
#' raw_spread(a, 10, 3, 3, square = FALSE, symmetrical =  FALSE) 
#' 
#' # Destination resistance used with each step
#' raw_spread(a, 10, 3, 3, square = FALSE, symmetrical = TRUE)  
#' 
#' 
#' # Square: the diagonal cost same as orthogonal 
#' a[,] <- 1
#' raw_spread(a, 10, 3, 3, square = TRUE, symmetrical =  FALSE) 
#' 
#' @export 
raw_spread <- function(x, spread_value, row, col, square = FALSE, 
                       symmetrical = TRUE){
	x<-as.matrix(x)  # so dim call works properly
	row <- as.integer(row)
	col <- as.integer(col)
	rows <- as.integer(dim(x)[1])
	columns <- as.integer(dim(x)[2])
	spread_value <- as.double(spread_value)	
	
	# square means short diagonals 
	use_long_diag <- !as.logical(square) |> as.integer()
	stopifnot(use_long_diag %in% c(0, 1))
	
	symmetrical <- as.integer(symmetrical)
	stopifnot(symmetrical %in% c(0, 1))
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
			use_long_diag, 
		  symmetrical,
			PACKAGE="resistantkernel")
	if (error.msg < 0) stop("spread function in dll/so reported error")
	
	matrix(result[[6]],rows, columns, byrow=TRUE)
	} # End r.spread function Definition


