raw.spread <- function(x, spread.value, row, col){
	x<-as.matrix(x)  # so dim call works properly
	row <- as.integer(row)
	col <- as.integer(col)
	rows <- as.integer(dim(x)[1])
	columns <- as.integer(dim(x)[2])
	spread.value <- as.double(spread.value)	
	x<-as.double(as.vector(t(x))) #convert to vector for passing to C
	
	error.msg <- as.integer(0)
	
	result<-.C("rspread", 
			as.double(spread.value), 
			as.integer(row), 
			as.integer(col), 
			as.integer(rows), 
			as.integer(columns),
			as.double(x),
			as.integer(error.msg),
			PACKAGE="spread")
	if (error.msg < 0) stop("spread function in dll/so reported error")
	
	matrix(result[[6]],rows, columns, byrow=TRUE)
	} # End r.spread function Definition

