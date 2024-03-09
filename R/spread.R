#' Calculate a Gaussian  resistant kernel
#' 
#' Calculates a Gaussian spread (resistant kernel)
#' 
#' 
#' @param x a matrix of resistance values all >=1
#' @param row the focal row of the spread
#' @param col the focal column of the spread
#' @param sd the standard deviation of the gaussian function in cost length
#' (resistance * physical distance) - the resulting spread will have this sd if
#' applied to a minimally resistant surface (all 1's)
#' @param cellsize the size of each cell (in physical units)
#' @param sd.threshold the number of standard deviations beyond which the
#' height of the surface isn't calculated
#' @return a matrix with the same dimensions as \code{x} but representing a
#' guassian spread from the focal cell.
#' @note The height of the kernel returned is dependent on the sd and is the
#' same as you'd get by calling \code{dnorm(cost.length.to.center, sd=sd)}.
#' One side effect of this is that the larger the sd the lower the height.  You
#' can normalize this by dividing the resultant kernel by dnorm(0, sd=sd) which
#' would then make the height at the center of the kernel 1.
#' @author Ethan Plunkett
#' @seealso [raw_spread]
#' @references Compton, B. W, McGarigal, K., Cushman, S. A. and Gamble, L. R.
#' A Resistant-Kernel Model of Connectivity for Amphibians that Breed in Vernal
#' Pools. \emph{Conservation Biology} \bold{21}, 788-799.
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
#' curve(dnorm(x, 3, 3), add=TRUE)
#' 
#' @export spread
spread <- function(x, row, col, sd, cellsize=1, sd.threshold=3){
	
  sd_cell <- sd/cellsize  #convert to cell units
						
	bank_account <- ceiling(sd_cell*sd.threshold)
		# make the bank account big enough to reach out to the 
		# threshold in a minimally resistant landscape 
		
	result <- raw_spread(x=x, spread_value=bank_account, row=row, col=col)
		# raw_spread returns the result of linear decay in the bank account (1  per cell) given a minimally resistant landscape

	# calculate distance to focal cell in physical (not cell size) units - accounting for resitance
	dist_to_center <- (bank_account-result)*cellsize  
	gaussian_result <- stats::dnorm(dist_to_center, mean=0, sd=sd)
		
	# Cleanup:
	gaussian_result[dist_to_center > sd.threshold*sd] <- 0
	gaussian_result[result==0]<-0	# This may be redundant.
					
	gaussian_result
} # end spread function definition

