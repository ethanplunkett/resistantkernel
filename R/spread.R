`spread` <-
function(x, f.row, f.col, sd, cell.size=1, sd.threshold=3){

	sd.cell <- sd/cell.size  #convert to cell units
						
	bank.account <- ceiling(sd.cell*sd.threshold)
		# make the bank account big enough to reach out to the 
		# threshold in a minimally resistant landscape 
		
	result <- raw.spread( (bank.account), f.row, f.col, x)
		# raw.spread returns the result of linear decay in the bank account (1  per cell) given a minimally resistant landscape

	# calculate distance to focal cell in physical (not cell size) units - accounting for resitance
	dist.to.center <- (bank.account-result)*cell.size  
	gaussian.result <- dnorm(dist.to.center, mean=0, sd=sd)
		
	# Cleanup:
	gaussian.result[dist.to.center > sd.threshold*sd] <- 0
	gaussian.result[result==0]<-0	# This may be redundant.
					
	gaussian.result
} # end spread function definition

