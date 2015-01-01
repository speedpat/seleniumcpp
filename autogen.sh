echo "Running libtoolize..."
libtoolize --force --copy

aclocalinclude="$ACLOCAL_FLAGS -I m4"
echo "Running aclocal $aclocalinclude ..."
aclocal $aclocalinclude
 
echo "Running autoheader..."
autoheader

echo "Running automake..."
automake --add-missing --foreign  $am_opt

echo "Running autoconf ..."
autoconf

echo "You could now exec ./configure --help to see available options"


