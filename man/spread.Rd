\name{spread}
\alias{spread}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{ calculate a Gaussian spread (resistant kernel) }
\description{
  calculates a gaussian spread over a resistant surface.
}
\usage{
spread(x, row, col, sd, cellsize = 1, sd.threshold = 3)
}
\arguments{
  \item{x}{ a matrix of resistance values all >=1 }
  \item{row}{ the focal row of the spread }
  \item{col}{ the focal column of the spread }
  \item{sd}{ the standard deviation of the gaussian function in cost length (resistance * physical distance) - the resulting spread will have this sd if applied to a minimally resistant surface (all 1's)}
  \item{cellsize}{ the size of each cell (in physical units)  }
  \item{sd.threshold}{ the number of standard deviations beyond which the height of the surface isn't calculated }
}

\value{
 a matrix with the same dimensions as \code{x} but representing a guassian spread from the focal cell. }
\references{ Compton, B. W, McGarigal, K., Cushman, S. A. and Gamble, L. R.  A Resistant-Kernel Model of Connectivity for Amphibians that Breed in Vernal Pools. \emph{Conservation Biology} \bold{21}, 788-799.
 }
\author{ Ethan Plunkett }
\note{ The height of the kernel returned is dependent on the sd and is the same as you'd get by calling \code{dnorm(cost.length.to.center, sd=sd)}.  One side effect of this is that the larger the sd the lower the height.  You can normalize this by dividing the resultant kernel by dnorm(0, sd=sd) which would then make the height at the center of the kernel 1. 
}
\seealso{  \code{\link{raw.spread}}  }
\examples{

# a minimally resistant matrix:
b <- matrix(1, 10, 10)

# the resulting spread
image(spread(b, 3, 3, 3) / dnorm(0, sd=3)  )

# a cross section of the spread compared to dnorm()
plot(spread(b, 3, 3, 3)[,3])
curve(dnorm(x, 3, 3), add=TRUE)

# add a higher resistance band
b[5,] <- 3

image(spread(b, 3, 3, 3) / dnorm(0, sd=3)  )

plot(spread(b, 3, 3, 3)[,3])
curve(dnorm(x, 3, 3), add=TRUE)
}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
\keyword{ resistant kernel }
\keyword{ gaussian spread }
\keyword{ spread }
