#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ELEMENT(m, i, j) (m)->matrix[(i) * (m)->cols + (j)]

struct matrix {
	long double	*matrix;
	size_t		rows;
	size_t		cols;
};

struct lup_triplet {
	struct matrix	*lower;
	struct matrix	*upper;
	struct matrix	*permutation;
};

void matrix_print(const struct matrix *m);

long double
dot_product(const long double *a, const long double *b, size_t sz)
{
	long double res;
	size_t i;

	for (i = 0, res = 0; i < sz; i++)
		res += a[i] * b[i];

	return res;

}

struct matrix *
matrix_create(size_t rows, size_t cols)
{
	struct matrix *m;

	if (!(m = (struct matrix *)malloc(sizeof(struct matrix)))) {
		perror("matrix_create");
		return NULL;
	}

	if (!(m->matrix = (long double *)malloc(rows * cols * sizeof(long double)))) {
		perror("matrix_create");
		return NULL;
	}

	m->rows = rows;
	m->cols = cols;

	return m;
}

struct matrix *
matrix_clone(const struct matrix *m)
{
	struct matrix *res;

	if (!(res = matrix_create(m->rows, m->cols)))
		return NULL;

	memcpy(res->matrix, m->matrix, m->rows * m->cols * sizeof(long double));

	return res;
}

void
matrix_destroy(struct matrix *m)
{
	free(m->matrix);
	free(m);
}

struct matrix *
matrix_create_null(size_t n)
{
	struct matrix *m;

	if (!(m = matrix_create(n, n)))
		return NULL;

	memset(m->matrix, 0, n * n * sizeof(long double));

	return m;
}

struct matrix *
matrix_create_identity(size_t n)
{
	struct matrix *m;
	size_t i;

	if (!(m = matrix_create_null(n)))
		return NULL;

	for (i = 0; i < n; i++)
		ELEMENT(m, i, i) = 1;
	
	return m;
}

void
_matrix_swap_row(struct matrix *m, size_t r1, size_t r2) {
	long double tmp;
	size_t i;

	for (i = 0; i < m->cols; i++) {
		tmp = ELEMENT(m, r1, i);
        	ELEMENT(m, r1, i) = ELEMENT(m, r2, i);
        	ELEMENT(m, r2, i) = tmp;
	}
}

long double *
matrix_get_column(const struct matrix *m, size_t col)
{
	long double *res;
	size_t i;

	if (!(res = (long double *)malloc(m->rows * sizeof(long double)))) {
		perror("matrix_get_column");
		return NULL;
	}

	for (i = 0; i < m->rows; i++)
		res[i] = ELEMENT(m, i, col);

	return res;
}

struct matrix *
matrix_opposite(const struct matrix *m)
{
	struct matrix *res;
	size_t i, j;

	if (!(res = matrix_clone(m)))
		return NULL;

	for (i = 0; i < m->rows; i++)
		for (j = 0; j < m->cols; j++)
			ELEMENT(res, i, j) = ELEMENT(m, i, j) * -1;

	return res;
}

struct matrix *
matrix_transpose(const struct matrix *m)
{
	struct matrix *res;
	long double *col;
	size_t i, j;

	if (!(res = matrix_create(m->cols, m->rows)))
		return NULL;

	for (i = 0; i < m->cols; i++) {
		col = matrix_get_column(m, i);
		for (j = 0; j < res->cols; j++)
			ELEMENT(res, i, j) = col[j];
		free(col);
	}

	return res;
}

struct lup_triplet *
matrix_lup_decompose(const struct matrix *m, int pivoting)
{
	struct lup_triplet *res;
	long double factor;
	size_t i, j, k, max_pivot;

	if (!(res = (struct lup_triplet *)malloc(sizeof(struct lup_triplet)))) {
		perror("matrix_lup_decompose");
		return NULL;
	}

	res->lower = matrix_create_null(m->rows);
	res->upper = matrix_clone(m);
	res->permutation = matrix_create_identity(m->rows);

	for (i = 0; i < res->upper->rows; i++) {
		max_pivot = i;

		for (j = i + 1; j < res->upper->rows; j++)
			if (fabsl(ELEMENT(res->upper, max_pivot, i)) < fabsl(ELEMENT(res->upper, j, i)))
				max_pivot = j;

		if (max_pivot != i && pivoting != 0) {
			_matrix_swap_row(res->upper, i, max_pivot);
			_matrix_swap_row(res->permutation, i, max_pivot);
			_matrix_swap_row(res->lower, i, max_pivot);
		}

		if (fabsl(ELEMENT(res->upper, i, i)) < LDBL_EPSILON)
			return NULL;
		for (j = i + 1; j < res->upper->rows; j++) {
			factor = ELEMENT(res->upper, j, i)/ELEMENT(res->upper, i, i);
			ELEMENT(res->lower, j, i) = factor;
			for (k = i; k < res->upper->cols; k++)
				ELEMENT(res->upper, j, k) -= ELEMENT(res->upper, i, k) * factor;
		}
	}

	for (i = 0; i < res->lower->rows; i++)
		ELEMENT(res->lower, i, i) = 1;

	return res;
}

void
matrix_lup_triplet_destroy(struct lup_triplet *lup)
{
	free(lup->lower->matrix);
	free(lup->upper->matrix);
	free(lup->permutation->matrix);
	free(lup->lower);
	free(lup->upper);
	free(lup->permutation);
	free(lup);
}

struct matrix *
matrix_add(const struct matrix *a, const struct matrix *b)
{
	struct matrix *res;
	size_t i, j;

	if (a->rows != b->rows || a->cols != b->cols) {
		errno = EINVAL;
		return NULL;
	}

	if (!(res = matrix_create(a->rows, a->cols)))
		return NULL;

	for (i = 0; i < res->rows; i++)
		for (j = 0; j < res->cols; j++)
			ELEMENT(res, i, j) = ELEMENT(a, i, j) + ELEMENT(b, i, j);

	return res;
}

struct matrix * 
matrix_subtract(const struct matrix *a, const struct matrix *b)
{
	struct matrix *opposite, *res;

	if (!(opposite = matrix_opposite(b)))
		return NULL;

	res = matrix_add(a, opposite);
	matrix_destroy(opposite);

	return res;
}

struct matrix *
matrix_multiply(const struct matrix *a, const struct matrix *b)
{
	struct matrix *res;
	size_t i, j;

	if (a->cols != b->rows) {
		errno = EINVAL;
		return NULL;
	}

	res = matrix_create(a->rows, b->cols);

	for (i = 0; i < res->rows; i++)
		for (j = 0; j < res->cols; j++)
			ELEMENT(res, i, j) = dot_product(&ELEMENT(a, i, 0), matrix_get_column(b, j), a->cols);

	return res;
}

struct matrix *
matrix_forward_substitute(const struct matrix *a, const struct matrix *rhs)
{
	struct matrix *res;
	size_t i, j;

	res = matrix_create(a->cols, 1);

	for (i = 0; i < a->rows; i++) {
		ELEMENT(res, i, 0) = ELEMENT(rhs, i, 0);
		for (j = 0; j < i; j++)
			ELEMENT(res, i, 0) -= ELEMENT(a, i, j) * ELEMENT(res, j, 0);
	}

	return res;
}

struct matrix *
matrix_backward_substitute(const struct matrix *a, const struct matrix *rhs)
{
	struct matrix *res;
	size_t i, j;

	res = matrix_create(a->cols, 1);

	for (i = a->rows - 1; i != (size_t)-1; i--) {
		ELEMENT(res, i, 0) = ELEMENT(rhs, i, 0);
		for (j = i + 1; j < a->cols; j++)
			ELEMENT(res, i, 0) -= ELEMENT(a, i, j) * ELEMENT(res, j, 0);
		ELEMENT(res, i, 0) /= ELEMENT(a, i, i);
	}

	return res;
}

struct matrix *
system_solve(const struct matrix *a, const struct matrix *rhs)
{
	struct lup_triplet *lup;
	struct matrix *perm_rhs, *res, *y;

	if (!(lup = matrix_lup_decompose(a, 1)))
		return NULL;

	puts("LOWER:");
	matrix_print(lup->lower);
	puts("UPPER:");
	matrix_print(lup->upper);
	puts("PERMUTATION:");
	matrix_print(lup->permutation);
	puts("RHS:");
	matrix_print(rhs);
	puts("PA = LU:");
	matrix_print(matrix_multiply(lup->permutation, a));
	matrix_print(matrix_multiply(lup->lower, lup->upper));

	perm_rhs = matrix_multiply(lup->permutation, rhs);
	y = matrix_forward_substitute(lup->lower, perm_rhs);
	res = matrix_backward_substitute(lup->upper, y);

	matrix_destroy(y);
	matrix_destroy(perm_rhs);
	matrix_lup_triplet_destroy(lup);

	return res;
}

long double
matrix_get_determinant(const struct matrix *m)
{
	struct lup_triplet *lup;
	struct matrix *perm;
	long double res;
	size_t i, j, swaps;
	int sign;

	if (!(lup = matrix_lup_decompose(m, 1)))
		return 0;

	perm = matrix_clone(lup->permutation);

	for (i = 0, swaps = 0; i < perm->rows; i++) {
		if (ELEMENT(perm, i, i) < LDBL_EPSILON) {
			for (j = i + 1; j < perm->rows; j++) {
				if ((1 - ELEMENT(perm, j, i)) < LDBL_EPSILON) {
					_matrix_swap_row(perm, i, j);
					swaps++;
				}
			}	
		}
	}

	sign = (swaps % 2 == 0) ? 1 : -1;

	matrix_print(lup->upper);
	for (i = 1, res = ELEMENT(lup->upper, 0, 0); i < lup->upper->rows; i++)
		res *= ELEMENT(lup->upper, i, i);

	matrix_destroy(perm);
	matrix_lup_triplet_destroy(lup);

	return res * sign;
}

struct matrix *
matrix_invert(const struct matrix *m)
{
	struct lup_triplet *lup;
	struct matrix *y, *cur_col, *res;
	size_t i, j;

	if (!(lup = matrix_lup_decompose(m, 0)))
		return NULL;

	if (!(res = matrix_create(m->rows, m->cols)))
		return NULL;

	for (j = 0; j < m->cols; j++) {
		if (!(cur_col = matrix_create(m->rows, 1)))
			return NULL;

		cur_col->matrix = matrix_get_column(lup->permutation, j);
		
		y = matrix_forward_substitute(lup->lower, cur_col);
		
		matrix_destroy(cur_col);
		cur_col = matrix_backward_substitute(lup->upper, y);

		for (i = 0; i < m->rows; i++)
			ELEMENT(res, i, j) = ELEMENT(cur_col, i, 0);

		matrix_destroy(cur_col);
		matrix_destroy(y);
	}

	matrix_lup_triplet_destroy(lup);

	return res;

}

struct matrix *
matrix_read(const char *s)
{
	struct matrix *res;
	char *tok;
	char *s2;
	size_t i, rows, cols;

	s2 = strdup(s);

	for (i = 0, cols = 0; s2[i] && s2[i] != '\n'; i++)
		if (s2[i] == '\t' || s2[i] == ' ')
			cols++;

	for (rows = 0; s2[i]; i++)
		if (s2[i] == '\n')
			rows++;

	if (rows == 0 || cols == 0) {
		fputs("matrix_read: Empty matrix", stderr);
		return NULL;
	}

	if (!(res = matrix_create(rows, cols)))
		return NULL;

	for (i = 0, tok = strtok(s2, " \n\t"); tok; i++) {
		res->matrix[i] = strtold(tok, NULL);
		tok = strtok(NULL, " \n\t");
	}

	return res;
}

void
matrix_print(const struct matrix *m)
{
	size_t i, j;

	for (i = 0; i < m->rows; i++) {
		for (j = 0; j < m->cols; j++)
			printf("\t%Lf", ELEMENT(m, i, j));
		printf("\n");
	}
}

int
main(int argc, char **argv)
{
	long double a[][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
	long double b[][3] = {{10, 11, 12}, {13, 14, 15}, {16, 17, 18}};
	char c[] = "\t1\t2\t3\n\t4\t5\t6\n\t7\t8\t9\n";
	long double d[][5] = {{2,3,-1,4,-5},{1,-4,2,-1,1},{3,1,4,-2,1},{-2,5,-3,1,-2},{1,2,1,3,-1}};
	long double e[][5] = {{7,3,6,-4,2}};
	long double f[][2] = {{4, 3}, {6, 3}};
	struct matrix m = {a[0], 3, 3};
	struct matrix n = {b[0], 3, 3};
	struct matrix o = {d[0], 5, 5};
	struct matrix p = {e[0], 5, 1};
	struct matrix q = {f[0], 2, 2};
	struct matrix r;

	matrix_print(system_solve(&o, &p));
	printf("%Lf\n", matrix_get_determinant(&o));
	matrix_print(matrix_invert(&o));
	matrix_print(matrix_transpose(&o));

	return 0;
}
