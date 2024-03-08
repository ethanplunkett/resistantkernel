# This tests for an error Noah discovered that according to Edi was produced by bad optimization inthe C compiler supported by R on windows
require(spread)
sd_meters<-1300
buffer <- 34
center <- buffer+1
data("resmat", package="spread")


# Broken call to spread (r function)
spr.out <- spread(x=res.mat,
		row=center,
		col=center, 
		sd=sd_meters, 
		cellsize=30)


# Broken call to raw.spread (r function)
	# Calculate arguments
	cell.size=30
	sd.cell <- sd_meters/cell.size
	sd.threshold = 3
  	bank.account <- ceiling(sd.cell * sd.threshold)
	f.row=center
	f.col=center
	x = res.mat

	# broken call to raw spread
	raw.spread(x=x, spread.value=bank.account, row=f.row, col=f.col)

# broken call to .C("spread")
	# calculate arguments
	x <- as.matrix(x)
    f.row <- as.integer(f.row)
    f.col <- as.integer(f.col)
    rows <- as.integer(dim(x)[1])
    columns <- as.integer(dim(x)[2])
    spread.value <- as.double(bank.account)
    x <- as.double(as.vector(t(x)))
    error.msg <- as.integer(0)
   result <- .C("rspread", as.double(spread.value), as.integer(f.row), 
        as.integer(f.col), as.integer(rows), as.integer(columns), 
        as.double(x), as.integer(error.msg), PACKAGE = "spread")






