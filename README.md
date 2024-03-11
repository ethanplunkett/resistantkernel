
# resistantkernel

<!-- badges: start -->
[![R-CMD-check](https://github.com/ethanplunkett/resistantkernel/actions/workflows/R-CMD-check.yaml/badge.svg)](https://github.com/ethanplunkett/resistantkernel/actions/workflows/R-CMD-check.yaml)
<!-- badges: end -->

The **resistantkernel** package calculates Compton et al. (2007) resistant
kernels.

`raw_spread()` creates a kernel that encodes the least cost path over a 
resistant surface from a focal cell to all neighboring cells.

`spread()` converts the raw kernel into a Gaussian function of the cost distance
to each neighboring cells.  In a minimally resistant surface the result matches
a Gaussian kernel. Higher resistance values increase the cost distance
to neighboring cells and compress the kernel.

Resistant kernels can be used to quantify how much and what parts of a
landscape is accessible to an animal with  a home range centered on, or 
starting a movement at a focal cell.  

Resistant kernels can also be used for variable width buffering around high 
value conservation land.
In this case the conservation value is converted to a resistant 
surface and then the kernel is initiated in one or many high value cells 
and the resulting surface thresholded to create a buffer that extends farther 
into higher value portions of the landscape.


## Installation

You can install the development version of **resistantkernel** from
[GitHub](https://github.com/) with:

``` r
# install.packages("devtools")
devtools::install_github("ethanplunkett/resistantkernel")
```

## Example

One use of resistantkernels is to calculate how much of a landscape is 
accessible to an animal at a particular point in space...   PENDING


# References 

Compton BW, McGarigal K, Cushman SA, Gamble LR. A resistant-kernel model of 
connectivity for amphibians that breed in vernal pools. Conserv Biol. 
2007 Jun;21(3):788-99. doi: 10.1111/j.1523-1739.2007.00674.x. PMID: 17531056
