This programm manage your book collection and fetches some informations about
books in your libary.


##Ui
###overview
- show a list as main view
- list is sortable and fieldvalues are title, author, rating, mark as soldable, mark as readed by name, sparte


- items are clickable -> opens the add new book
- right click -> submenu: edit, remove, mark as soldable, mark as readable -> different names


###sheet view
- show cover
- title, author, pages, isbn, rating
- show soldable
- show readed users
- editable


###add new book
- own dialog
- search books through isbn number (amazon, ...)
- editable fetched data
- if it not exists add a book manually


###user view
- show readed books
- show recomend books


##Storage
chooseable storage formats


- lSQL
- SQL
- filestorage


##Book fetcher
fetching book infos from internet


- search with isbn number
- search autor
- search title


##Build and Programming style
- cmake builds
- qt framework
- codestyle as openttd
- c++ / c