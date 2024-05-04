
import os
import requests
from bs4 import BeautifulSoup

def download_images_from_page(url = "https://duckduckgo.com/?va=n&t=hw&q=bears&iax=images&ia=images", destination_folder="downloaded_images"):
    headers = {
        "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/5373"
    }

    # Get page content
    response = requests.get(url, headers=headers)
    soup = BeautifulSoup(response.content, 'html.parser')

    # Find all image tags
    img_tags = soup.find_all('img')

    # Ensure destination directory exists
    if not os.path.exists(destination_folder):
        os.makedirs(destination_folder)

    # Download and save each image
    for img_tag in img_tags:
        img_url = img_tag["src"]

        # Handle relative URLs
        if not img_url.startswith(('data:image', 'http', 'https')):
            img_url = os.path.join(url, img_url)
        
        img_name = os.path.basename(img_url)
        img_path = os.path.join(destination_folder, img_name)
        
        img_data = requests.get(img_url).content
        with open(img_path, 'wb') as img_file:
            img_file.write(img_data)
            
        print(f"Downloaded {img_name} to {img_path}")

if __name__ == "__main__":
    # webpage_url = input("Enter the webpage URL: ")
    download_images_from_page()
