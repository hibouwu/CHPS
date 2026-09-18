
/*
 *  Scales an array
 */
  void
  dscal(int n,double sa,double sx[], int incx){
    int i,j;

    if (incx == 1) {
#pragma omp for
      for (i=0; i<n; i++)
        sx[i] *= sa;
    } else {
#pragma omp for private(j)
      for (i=0; i<n; i++) {
	  j = i*incx;
        sx[j] *= sa;
      }
    }
  }
