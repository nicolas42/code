Concurrently download http urls

    go run downloader.go

This will make a "downloads" directory and put the files into it. 
based on https://medium.com/@dhanushgopinath/concurrent-http-downloads-using-go-32fecfa1ed27


BUG

Currently, downloading txt files returns them as being empty.  