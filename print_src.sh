#for f in src/*.cpp src/*.h
for f in $(find src/ -name '*.cpp' -or -name '*.h')
do
    echo "Processing $f..."
    a2ps --line-numbers=1 "$f" -o "$f".ps
done

mkdir "print output"

#for f in src/*.ps
for f in $(find src/ -name '*.ps')
do
    b=$(basename $f)
    ps2pdf "$f" "print output/${b%.*}.pdf"
    rm "${f%.*}.ps"
done

cd 'print output'
pdfs=$(ls)
echo $pdfs
pdfunite $pdfs ../final_print.pdf
