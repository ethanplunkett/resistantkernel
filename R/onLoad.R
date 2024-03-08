.onLoad <- function(lib, pkg){
	library.dynam("spread", pkg, lib)
	cat("spread shared object loaded")
	}