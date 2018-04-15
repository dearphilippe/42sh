rm -rRf ../42sh_vgs/parse/*
cp -R * ../42sh_vgs/parse
cd ../42sh_vgs/parse
git add .
git commit -m "recopy into parse"
git push
