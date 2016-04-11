#include <stdlib.h>
#include <mpi.h>

#define RETURN_ON_MPIERR(rc) if ((rc) != MPI_SUCCESS) { return (rc); }

int Bcast_vdg(void* buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm)
{
    if (comm == MPI_COMM_NULL) {
        return MPI_ERR_COMM;
    }

    int comm_size;
    MPI_Comm_size(comm, &comm_size);
    int srcount = count / comm_size; //only for (count % comm_size == 0)
    int type_size;
    MPI_Type_size(MPI_CHAR, &type_size);
    void* local_buff = malloc(type_size * srcount);
    if (local_buff == NULL) {
        return MPI_ERR_BUFFER;
    }

    PMPI_Scatter(buffer, srcount, datatype, local_buff, srcount, datatype, root, comm);
    PMPI_Allgather(local_buff, srcount, datatype, buffer, srcount, datatype, comm);

    free(local_buff);

    return MPI_SUCCESS;
}

