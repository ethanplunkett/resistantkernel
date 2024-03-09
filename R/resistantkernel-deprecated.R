#' Deprecated function(s) in the resistantkernel package
#' 
#' These functions are provided for compatibility with older version of
#' the resistantkernel and the earlier \pkg{spread} and \pkg{gridprocess} 
#' packages.  They may eventually be completely removed.
#' 
#' @rdname resistantkernel-deprecated
#' @name resistantkernel-deprecated
#' @param ... Parameters to be passed to the current version of the functions
#' @return See current versions of functions.  
#' @keywords internal
NULL


#' @rdname resistantkernel-deprecated
#' @param x,row,col Passed as is to [raw_spread]
#' @param spread.value passed as `spread_value` to [raw_spread()]
#' @description `raw.spread()` has been replaced by [raw_spread()]
#' @export
raw.spread <- function(x, spread.value, row, col){
  .Deprecated("raw_spread", package = "resistantkernel")
  raw_spread(x, spread.value, row, col)
}