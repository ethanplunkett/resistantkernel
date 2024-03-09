\name{raw.spread}
\alias{raw.spread}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{ interface for the C++ spread code - mainly for internal use }
\description{
This function takes a spread value, the focal cell coordinates, and
a resistance matrix (all values >= 1); executes a resistant spread; and returns the final snapshot of the spread as a matrix.}
\usage{
raw.spread(x, spread.value, row, col)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{x}{ the resistance matrix, all values must be >= 1 }
  \item{spread.value}{ the initial bank account for the spread, which is depleted based on the resistance of each cell as the spread progresses.}
  \item{row}{ the focal row  of the spread }
  \item{col}{ the focal column of the spread }
  
}
\details{
	This calculates the functional proximity of each cell to the focal cell.  With the proximity highest at the focal cell where it is equal to the spread.value and diminishing with distance from the focal cell (based on the resistance of intervening cells).  The functional proximity thus is zero for cells with a functional distance greater than spread.value from the focal cell (regardless of how much greater). In practice larger spread values allow calculation of a larger functional distances but requires more processor time. }
\value{
	A matrix with the same dimensions as \code{x} the values of which represent the functional proximity to the focal cell.  They range from \code{spread.value} (at the focal cell) to zero for cells greater than \code{spread.value} away from the focal cell.  

}
\references{ ~put references to the literature/web site here ~ }
\author{ Ethan Plunkett }
\seealso{ \code{\link{spread}} }
\examples{

# Create (minimally resistant) test matrix 
a <- matrix(1, 5, 5)
a
raw.spread(10, 3, 3, a)

# Add two higher resistance bands
a[2, ]  <- 5
a[,2] <- 5
a
raw.spread(10, 3, 3, a)

}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
\keyword{ ~spread }
\keyword{ ~least cost path }