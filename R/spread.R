#' Calculate a Gaussian resistant kernel
#' 
#' @param x a matrix of resistance values all >=1
#' @param ... Arguments to be passed to other methods.
#' @param row the focal row of the spread
#' @param col the focal column of the spread
#' @param sd the standard deviation of the Gaussian function in cost length
#' (resistance * physical distance). The resulting spread will be equivalent
#' a Gaussian kernel with this standard deviation when applied to a minimally 
#' resistant surface: resistance of 1 for all cells.
#' @param cellsize the size of each cell in physical units, typically meters.
#' @param sd_threshold the number of standard deviations beyond which the
#' height of the surface is not calculated
#' @inheritParams raw_spread
#' @return a matrix with the same dimensions as `x` but representing a
#' Gaussian spread from the focal cell.
#' @note The height of the kernel returned is dependent on the `sd` and is the
#' same as you'd get by calling `dnorm(cost_dist_to_center, sd=sd)`.
#' One side effect of this is that the larger the `sd` the lower the height.
#' You can normalize this by dividing the resultant kernel by 
#' `dnorm(0, sd = sd)` which would then make the height at the center of
#' the kernel 1. 
#' @seealso [raw_spread]
#' @references Compton BW, McGarigal K, Cushman SA, Gamble LR. 
#' A resistant-kernel model of connectivity for amphibians that breed in 
#' vernal pools. Conserv Biol. 2007 Jun;21(3):788-99. 
#' doi: 10.1111/j.1523-1739.2007.00674.x. PMID: 17531056.
#' 
#' @examples
#' #' # a minimally resistant matrix:
#' b <- matrix(1, 10, 10)
#' 
#' # the resulting spread
#' image(spread(b, 3, 3, 3) / dnorm(0, sd=3)  )
#' 
#' # a cross section of the spread compared to dnorm()
#' plot(spread(b, 3, 3, 3)[,3])
#' curve(dnorm(x, 3, 3), add=TRUE)
#' 
#' # add a higher resistance band
#' b[5,] <- 3
#' 
#' image(spread(b, 3, 3, 3) / dnorm(0, sd=3)  )
#' 
#' plot(spread(b, 3, 3, 3)[,3])
#' abline(v = 5, col = "red") # location of higher resistance
#' curve(dnorm(x, 3, 3), add=TRUE)
#' 
#' @export
spread <- function(x, ...) UseMethod("spread")

#' @export
#' @rdname spread
spread.matrix <- function(x, row, col, sd, cellsize = 1, sd_threshold = 3, 
                   square = FALSE, symmetrical = TRUE, ...){
	
  sd_cell <- sd/cellsize  #convert to cell units
						
	bank_account <- ceiling(sd_cell*sd_threshold)
		# make the bank account big enough to reach out to the 
		# threshold in a minimally resistant landscape 
		
	result <- raw_spread(x=x, spread_value=bank_account, row=row, 
	                     col=col, square = square, symmetrical = symmetrical)
	# raw_spread returns the result of linear decay in the bank account 
	# (1  per cell) given a minimally resistant landscape

	# calculate distance to focal cell in physical (not cell size) units 
	# while accounting for resitance
	dist_to_center <- (bank_account-result)*cellsize  
	gaussian_result <- stats::dnorm(dist_to_center, mean=0, sd=sd)
		
	# Cleanup:
	gaussian_result[dist_to_center > sd_threshold*sd] <- 0
	gaussian_result[result==0]<-0	# This may be redundant.
					
	gaussian_result
} # end spread function definition



