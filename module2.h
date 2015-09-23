struct flight *read_file(char *file, int *cfs, int *cfl);

int fulldate(struct fulldate START, struct fulldate END, int *x);

struct cf *set(struct flight *F,
struct fulldate TO,
	int cfl,
	int *scf,
	int *fscf,
	double *IFT,
	int n);

struct cf *award(struct cf *CF, int n, int *P, double *IFT, double *V);
