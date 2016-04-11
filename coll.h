#ifndef COLL_H
#define COLL_H


int Bcast_vdg(void* buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm);

#endif /* COLL_H */
