/* -*- mode: c++; c-file-style: "engine"; c-basic-offset: 4; indent-tabs-mode: nil -*- */
/**
 * @file
 * @brief Matrix parameter wrapper for XMP
 *
 *
 *
 * 2012-01-12
 *
 */
#ifndef MATRIX_XMP_TYPE_HH
#define MATRIX_XMP_TYPE_HH 1

#include <stdlib.h>
#include <stdbool.h>
#include <mpi.h>

typedef double XMP_Matrix; /* Declaration of parameter type in XMP ( XMP_type )*/
typedef double* Matrix; /* Declaration of parameter type for import/export functions (type) */

/* */
static MPI_Datatype Matrix_MPI_Type()
{

	return MPI_DOUBLE;
}

// param_import / export definition for types that need data distribution in XMP

static bool Matrix_import(Matrix param, char* filename, const MPI_Datatype motif, const int size)
{
	int ack;
	MPI_File   fh;
	MPI_Status status;


	ack = MPI_File_open(MPI_COMM_WORLD,filename,MPI_MODE_RDONLY,MPI_INFO_NULL,&fh);

	if (ack != MPI_ERR_NO_SUCH_FILE)
	{
		MPI_File_set_view(fh, 0, MPI_DOUBLE, motif,"native", MPI_INFO_NULL);
		MPI_File_read_all(fh, param, size, MPI_DOUBLE, &status);
		MPI_File_close(&fh);
		return true;
	}

	MPI_File_close(&fh);
	return false;
}

static bool Matrix_export(const Matrix param, char* filename, const MPI_Datatype motif, const int size, MPI_Comm Communicator)
{
	int ack;
	MPI_File   fh;
	MPI_Status status;

	ack = MPI_File_open(Communicator,filename,MPI_MODE_WRONLY | MPI_MODE_CREATE,MPI_INFO_NULL,&fh);

	if (ack != MPI_ERR_NO_SUCH_FILE)
	{
		MPI_File_set_view(fh, 0, MPI_DOUBLE, motif ,"native", MPI_INFO_NULL);
		MPI_File_write_all(fh, param, size, MPI_DOUBLE, &status);
		MPI_File_close(&fh);
		return true;
	}

	MPI_File_close(&fh);
	return false;
}

#endif
