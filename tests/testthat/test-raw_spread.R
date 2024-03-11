test_that("raw_spread works with both values of symmetrical ", {
  
   # Create (minimally resistant) test matrix 
   res1 <- matrix(1, 5, 5)
   
   # In a uniform landscape both methods are the same
   expect_no_error(s1a <- raw_spread(res1, 10, 3, 3, FALSE, TRUE))
   expect_no_error(s1b <- raw_spread(res1, 10, 3, 3, FALSE, FALSE))
   expect_equal(s1a, s1b)
   expect_equal(s1a[3, ],  c(8, 9, 10, 9, 8))
   
   
   # Add two higher resistance bands
   res2 <- res1
   res2[2, ]  <- 5
   res2[,2] <- 5
   
   s2a <- raw_spread(res2, 10, 3, 3, FALSE, FALSE) # Average of source and destination resistance
   s2b <- raw_spread(res2, 10, 3, 3, FALSE, TRUE)  # Destination resistance
   
  
   expect_snapshot(s2a)
   
   expect_snapshot(s2b)
   
   
})



test_that("raw_spread works with square = TRUE", {
  res <- matrix(1, 5, 5)
  square <- raw_spread(res, 10, 3, 3, TRUE, FALSE)
  expect_snapshot(square)
  
})
