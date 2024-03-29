# March 2024 changes:

  * Add argument `symmetrical` which controls whether each step in the spread
  uses both the source and destination cell resistances or only the destination
  cell resistance (as in the original algorithm).
  * Address a bunch of package check issues.
  * Add github action to check package against Windows, Ubuntu, and MacOS.
  * Add unit testing.
  * Switch to roxygen2 Documentation.
  * Switch to semantic versioning.
  * Import changes made in Edi's code base.
  * Convert to snake_case naming convention.
  * Check spelling
  * Lint
  

# Brief history of this project

**resistantkernel** is a mash up of code that has existed in several largely 
private packages for many years:

1.  *Early 2000's*:  Brad Compton develops the algorithm in APL.  Eduard Eni 
   implements it in C++.
2. *2009*: Paper published:
    Compton BW, McGarigal K, Cushman SA, Gamble LR. 
    A resistant-kernel model of connectivity for amphibians that breed in 
    vernal pools. Conserv Biol. 2007 Jun;21(3):788-99. 
   doi: 10.1111/j.1523-1739.2007.00674.x. PMID: 17531056.
3. *2007 to 2009*: Early **spread** R package developed by Ethan Plunkett, 
   wrapping Eduard's code. Noah Charney uses **spread** package 
   in his dissertation and discovers that it very rarely hard crashes - this
   is attributed by Edi to compiler optimization in R's toolchain.
4. *2009 to present*: Landscape ecology lab's **gridio** package is developed and maintained 
   This linked to a DLL compiled by Eduard in MS Visual 
   Studio that provided the resistant kernel algorithm (and a lot of other
   stuff) in a non-portable, Windows only way.  **spread** package moth balled.
5. *2019 to present*: Parts of **gridio** are broken into new packages
   **gridprocess** gets the resistant kernel algorithm in internal precompiled
   DLL's.  This adds 64 bit support but is not cross platform nor CRAN 
   compatible.
6. *March 2024:*  **resistantkernel** package is created from the ashes of the 
   old **spread** package with integrated CRAN compatible, cross-platform C++ 
   code. 
7. *pending*: **gridprocess** drops pre-compiled DLLs and instead imports 
   **resistantkernel**
   
   

