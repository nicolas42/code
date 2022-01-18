rebol [
    doc: {
    === NIT VERSION CONTROL SYSTEM ===
    because I can't remember how git revert works

    The versions are stored in .nit/versions/<date-time>
    The files are stored in .nit/files/<sha1-hash> 
    }
]

file-walk: func [
	{Deep read a directory given a dir d
	an output block o and a boolean function fn}
	dir a_function /local file
] [
	file: read dir
	foreach file file [ do :a_function dir/:file ]
	foreach file file [ if #"/" = last file [ file-walk dir/:file :a_function ] ]
]

zero-extend: funct [ a n ] [ a: mold a  head insert/dup a "0" n - length? a ]

now-descending: funct [ ] [
	now-time: replace/all mold now/time ":" ""
	rejoin [ "" zero-extend now/year 4 zero-extend now/month 2 zero-extend now/day 2 "-" now-time ]
]

init: funct [ ] [

	attempt probe [
        make-dir %.nit/
        make-dir %.nit/files/
        make-dir %.nit/versions/
	]

]

commit: funct [ ] [

	version: copy [ ] 
	file-walk %. func [ filename ] [ 
	
		if find/match filename "./.nit" [ return ]
		
		filename_sha1: join %./.nit/files/ mold checksum/method filename 'sha1
		foreach c "#{}" [ replace/all filename_sha1 c "" ]
		write filename_sha1 read filename
		append version filename_sha1  
        append version filename   
	]   
	write/lines rejoin [ %.nit/versions/ now-descending ] version
	forskip version 2 [ print rejoin [ version/2 " => " version/1 ] ]
]


revert: funct [ version-file ] [

	version: read/lines version-file
	foreach f read %. [ if not find/match f ".nit" [ either dir? f [ delete-dir f ] [ delete f ] ] ]
	forskip version 2 [ print rejoin [ version/1 " => " version/2 ] attempt [ write to-file version/2 read to-file version/1 ] ]
]

