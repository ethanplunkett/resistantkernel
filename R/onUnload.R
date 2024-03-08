.onUnload <- function(libpath){
  library.dynam.unload("spread", libpath)
  cat("spread shared object loaded")
}

