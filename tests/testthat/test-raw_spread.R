test_that("raw_spread works", {
  
   # Create (minimally resistant) test matrix 
   res1 <- matrix(1, 5, 5)
   
   # In a uniform landscape both methods are the same
   expect_no_error(s1a <- raw_spread(res1, 10, 3, 3, TRUE))
   expect_no_error(s1b <- raw_spread(res1, 10, 3, 3, FALSE))
   expect_equal(s1a, s1b)
   expect_equal(s1a[3, ],  c(8, 9, 10, 9, 8))
   
   
   # Add two higher resistance bands
   res2 <- res1
   res2[2, ]  <- 5
   res2[,2] <- 5
   
   s2a <- raw_spread(res2, 10, 3, 3, FALSE) # Average of source and destination resistance
   s2b <- raw_spread(res2, 10, 3, 3, TRUE)  # Destination resistance
   
  
   expect_snapshot(s2a)
   
   expect_snapshot(s2b)
   
   
   
})
