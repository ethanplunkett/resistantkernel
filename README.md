
# resistantkernel

<!-- badges: start -->
<!-- badges: end -->

The goal of resistantkernel is to share the Compton et. al. (2007) resistant
kernel algorithm. Which encodes the least cost path over a resistant surface
from a focal cell to all neighboring cells.  

It is ussually converted into a gaussian function of the cost distance
to each neighboring cell such that in a minimally resistant surface it 
matches a gaussian kernel. Higher resistance values increase the cost distance
to neighboring cells and consequently compress the kernel.

It can be used to assess how much of a landscape is accessible to an animal with 
a home range centered on a focal cell, or to an animal starting a movement
at a focal cell.  

It can also be used for variable width buffering around high value conservation
land.  In this case the conservation value can be converted to a resistant 
surface and then the kernel  can be initiated in one or many high value cells 
and the resulting surface thresholded to create a buffer that extends farther 
into higher value portions of the landscape.

## Beta version

This is a beta version of the package and is not yet fully functional. 
Use with caution.

## Installation

You can install the development version of resistantkernel from
[GitHub](https://github.com/) with:

``` r
# install.packages("devtools")
devtools::install_github("ethanplunkett/resistantkernel")
```

## Example

One use of resistantkernels is to calculate how much of a landscape is 
accessible to an animal at a particular point in space...   [more pending]


# References 

Compton BW, McGarigal K, Cushman SA, Gamble LR. A resistant-kernel model of 
connectivity for amphibians that breed in vernal pools. Conserv Biol. 
2007 Jun;21(3):788-99. doi: 10.1111/j.1523-1739.2007.00674.x. PMID: 17531056
