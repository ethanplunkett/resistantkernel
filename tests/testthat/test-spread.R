test_that("noah's spread bug is avoided", {
  
  # This tests for an error Noah discovered ~2009
  # that according to Edi was produced by bad optimization in the C compiler 
  # used by R on windows
  
  # The error occured after many (millions?) of randomized calls to spread
  # during an optimization routine.
  # When it occured R would hard crash (close abruptly)
  
  sd_meters <- 1300
  buffer <- 34
  center <- buffer+1
  res.mat <- noah_res_mat
  
  # Broken call to spread (r function)
  expect_no_error(
    spr.out <- spread(x=res.mat,
                      row=center,
                      col=center, 
                      sd=sd_meters, 
                      cellsize=30)
  )
  
  # Broken call to raw_spread (r function)
  # Calculate arguments
  cell.size=30
  sd_cell <- sd_meters/cell.size
  sd_threshold = 3
  bank_account <- ceiling(sd_cell * sd_threshold)
  f_row=center
  f_col=center
  x = res.mat
  
  # broken call to raw spread
  expect_no_error(
    raw_spread(x=x, spread_value=bank_account, row=f_row, col=f_col)
  )
  # broken call to .C("spread")
  # calculate arguments
  x <- as.matrix(x)
  f_row <- as.integer(f_row)
  f_col <- as.integer(f_col)
  rows <- as.integer(dim(x)[1])
  columns <- as.integer(dim(x)[2])
  spread_value <- as.double(bank_account)
  x <- as.double(as.vector(t(x)))
  error_msg <- as.integer(0)
  
  expect_no_error(
    result <- .C("rspread", as.double(spread_value), as.integer(f_row), 
                 as.integer(f_col), as.integer(rows), as.integer(columns), 
                 as.double(x), as.integer(error_msg), PACKAGE = "resistantkernel")
  )
  
  
})
