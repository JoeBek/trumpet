import React, { useState } from 'react';
import axios from 'axios';

function FileUpload() {
  const [selectedFile, setSelectedFile] = useState(null);
  const [fileURL, setFileURL] = useState(""); // State to hold file URL

  const handleFileChange = (event) => {
    const file = event.target.files[0];
    setSelectedFile(file);

    // Check if the selected file is an image
    if (file && file.type.startsWith('image/')) {
      const reader = new FileReader();
      reader.onloadend = () => {
        setFileURL(reader.result); // Set file URL
      };
      reader.readAsDataURL(file);
    } else {
      setFileURL(""); // Reset file URL if not an image
    }
  };

  const handleUpload = () => {
    if (selectedFile) {
      const formData = new FormData();
      formData.append('file', selectedFile);
      
      axios.post('localhost/img', formData, {
        headers: {
          'Content-Type': 'multipart/form-data'
        }
      })
      .then(response => {
        // Handle success
        console.log('File uploaded:', response.data);
      })
      .catch(error => {
        // Handle error
        console.error('Error uploading file:', error);
      });

      console.log('File uploaded:', selectedFile);
    } else {
      console.log('No file selected');
    }
  };

  return (
    <div>
      {fileURL && (
        <div className="image-preview">
          <img src={fileURL} alt="Selected File" style={{ maxWidth: '100%', maxHeight: '200px' }} />
        </div>
      )} {/* Render image */}
      <div>
        <input type="file" onChange={handleFileChange} />
        <button onClick={handleUpload}>Upload</button>
      </div>
    </div>
  );
}

export default FileUpload;



