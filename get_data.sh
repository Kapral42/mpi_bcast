for t in mpi vdg ; do
    echo "Bcast $t"
    for size in 8 16 32 64 128 256 512 ; do
        python ./max_time.py ./${1}/${t}_bc_${size}.log
    done
    echo
done
