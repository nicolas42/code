// web scrape from google images with something like this

// urls = Array.from(document.querySelectorAll('.rg_di .rg_meta')).map(el=>JSON.parse(el.textContent).ou);
// window.open('data:text/csv;charset=utf-8,' + escape(urls.join('\n')));

// urls=[]; document.querySelectorAll('img').forEach(function(img){urls.push(img.src)})
// window.open('data:text/csv;charset=utf-8,' + escape(urls.join('\n')));

// based on based on https://medium.com/@dhanushgopinath/concurrent-http-downloads-using-go-32fecfa1ed27

package main

import (
	"bufio"
	"bytes"
	"errors"
	"fmt"
	"io"
	"io/ioutil"
	"log"
	"net/http"
	"os"
	"path/filepath"
	"strconv"
)



func main() {

	var output_dir = "project_gutenberg"

	urls := []string{}
    for i:=1; i<100000; i+=1 {
        urls = append(urls, "https://www.gutenberg.org/files/" + strconv.Itoa(i) +"/"+ strconv.Itoa(i) +".txt")
        urls = append(urls, "https://www.gutenberg.org/files/" + strconv.Itoa(i) +"/"+ strconv.Itoa(i) +"-0.txt")
	}

	// urls := []string{ "https://www.gutenberg.org/files/1/1.txt", "https://www.gutenberg.org/files/1/1-0.txt", "https://www.gutenberg.org/files/2/2.txt", "https://www.gutenberg.org/files/2/2-0.txt", "https://www.gutenberg.org/files/3/3.txt", "https://www.gutenberg.org/files/3/3-0.txt", "https://www.gutenberg.org/files/4/4.txt", "https://www.gutenberg.org/files/4/4-0.txt", "https://www.gutenberg.org/files/5/5.txt", "https://www.gutenberg.org/files/5/5-0.txt", "https://www.gutenberg.org/files/6/6.txt", "https://www.gutenberg.org/files/6/6-0.txt", "https://www.gutenberg.org/files/7/7.txt", "https://www.gutenberg.org/files/7/7-0.txt", "https://www.gutenberg.org/files/8/8.txt", "https://www.gutenberg.org/files/8/8-0.txt", "https://www.gutenberg.org/files/9/9.txt", "https://www.gutenberg.org/files/9/9-0.txt", "https://www.gutenberg.org/files/10/10.txt", "https://www.gutenberg.org/files/10/10-0.txt", "https://www.gutenberg.org/files/11/11.txt", "https://www.gutenberg.org/files/11/11-0.txt", "https://www.gutenberg.org/files/12/12.txt", "https://www.gutenberg.org/files/12/12-0.txt", "https://www.gutenberg.org/files/13/13.txt", "https://www.gutenberg.org/files/13/13-0.txt", "https://www.gutenberg.org/files/14/14.txt", "https://www.gutenberg.org/files/14/14-0.txt", "https://www.gutenberg.org/files/15/15.txt", "https://www.gutenberg.org/files/15/15-0.txt", "https://www.gutenberg.org/files/16/16.txt", "https://www.gutenberg.org/files/16/16-0.txt", "https://www.gutenberg.org/files/17/17.txt", "https://www.gutenberg.org/files/17/17-0.txt", "https://www.gutenberg.org/files/18/18.txt", "https://www.gutenberg.org/files/18/18-0.txt", "https://www.gutenberg.org/files/19/19.txt", "https://www.gutenberg.org/files/19/19-0.txt", "https://www.gutenberg.org/files/20/20.txt", "https://www.gutenberg.org/files/20/20-0.txt", "https://www.gutenberg.org/files/21/21.txt", "https://www.gutenberg.org/files/21/21-0.txt", "https://www.gutenberg.org/files/22/22.txt", "https://www.gutenberg.org/files/22/22-0.txt", "https://www.gutenberg.org/files/23/23.txt", "https://www.gutenberg.org/files/23/23-0.txt" }
	// fmt.Println(urls)

	if _, err := os.Stat(output_dir); os.IsNotExist(err) {
		os.Mkdir(output_dir, 0777)
	}

	// Download the files
	fmt.Printf("Downloading to %s directory...", output_dir)
	download_files_in_parallel(urls, output_dir)
}

func download_files_in_parallel(urls []string, output_dir string) ([][]byte, error) {
	done := make(chan []byte, len(urls))
	errch := make(chan error, len(urls))
	for _, url := range urls {
		go func(url string) {
			b, err := download_and_write_file(url, output_dir)
			if err != nil {
				errch <- err
				done <- nil
				return
			}
			done <- b
			errch <- nil
		}(url)
	}
	bytesArray := make([][]byte, 0)
	var errStr string
	for i := 0; i < len(urls); i++ {
		bytesArray = append(bytesArray, <-done)
		if err := <-errch; err != nil {
			errStr = errStr + " " + err.Error()
		}
	}
	var err error
	if errStr != "" {
		err = errors.New(errStr)
	}
	return bytesArray, err
}

func download_and_write_file(url string, output_dir string) ([]byte, error) {

	response, err := http.Get(url)
	if err != nil {
		return nil, err
	}
	defer response.Body.Close()
	if response.StatusCode != http.StatusOK {
		return nil, errors.New(response.Status)
	}
	var data bytes.Buffer
	_, err = io.Copy(&data, response.Body)
	if err != nil {
		return nil, err
	}

	filename := filepath.Join(output_dir, filepath.Base(url))
	err = ioutil.WriteFile(filename[0:min(100, len(filename))], data.Bytes(), 0644)
	if err != nil {
		log.Fatal(err)
	}
	fmt.Println(url)
	return data.Bytes(), nil
}

func read_file_into_lines(path string) ([]string, error) {
	file, err := os.Open(path)
	if err != nil {
		return nil, err
	}
	defer file.Close()

	var lines []string
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		lines = append(lines, scanner.Text())
	}
	return lines, scanner.Err()
}

func min(a, b int) int {
	if a < b {
		return a
	}
	return b
}
