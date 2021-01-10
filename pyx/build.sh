
# pd.pyx
python setup.py build_ext --inplace
rm -rf ./build ./pd.c
# python -c "import pd"
python go.py


# pylibpd.pyx
# python setup.py build_ext --inplace
# rm -rf ./build ./pylibpd.c
# python -c "import pd"
# python go.py

