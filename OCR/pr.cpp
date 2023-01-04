#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>


#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>


#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace cv;
using namespace std;
using namespace tesseract;


int main() {

	VideoCapture cap(0);
	Mat img, img_BW;

	CascadeClassifier plateCascade;
	plateCascade.load("Resources/haarcascade_russian_plate_number.xml");

	if (plateCascade.empty()) { cout << "XML file not loaded" << endl; }

	vector<Rect> plates;
	bool h = true;
	while (h) {
		cap.read(img);

		plateCascade.detectMultiScale(img, plates, 1.1, 10);

		for (int i = 0; i < plates.size(); i++)
		{
			Mat imgCrop = img(plates[i]); // cropping the image upto rectangle

			cvtColor(imgCrop, img_BW, COLOR_BGR2GRAY); //changing colour of image to black and white
			
			imwrite("Resources/Plates/" + to_string(i) + ".png", img_BW); // saving the image

			rectangle(img, plates[i].tl(), plates[i].br(), Scalar(0, 0, 255), 2);


			char* outText; 

			TessBaseAPI* api = new TessBaseAPI(); // creating object of a class
			// Initialize tesseract-ocr with English, without specifying tessdata path
			
			
			if (api->Init("C:\\LIBRARIES\\tessdata", "eng")) {
				fprintf(stderr, "Could not initialize tesseract.\n"); // stderr is standered error
				exit(1); // exit(0) is normal termination of program and 1 is abnormal termination like error
			}

			// Open input image with leptonica library--  Its used for image prossessing and anylaysing 
			Pix* image = pixRead("J:\\C CPP\\OCR\\OCR\\Resources\\Plates\\0.png"); // importing image in its binary form for text extraction
			api->SetImage(image); // Setting the image in api used for text extraction


			// Get OCR result
			outText = api->GetUTF8Text(); // its a common character encoding
			printf("OCR output:\n Number Plate : %s", outText); // printing that text dected as output in terminal



			string s1 = outText;
		
			
			transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
			
			if (s1.substr(0, 2) == "an") { printf("State : Andaman and Nicobar Islands\n\n"); }
			else if (s1.substr(0, 2) == "ap") { printf("State : Andhra Pradesh\n\n"); }
			else if (s1.substr(0, 2) == "ar") { printf("State : Arunachal Pradesh\n\n"); }
			else if (s1.substr(0, 2) == "as") { printf("State : Assam\n\n"); }
			else if (s1.substr(0, 2) == "br") { printf("State : Bihar\n\n"); }
			else if (s1.substr(0, 2) == "ch") { printf("State : Chandigarh\n\n"); }
			else if (s1.substr(0, 2) == "dn") { printf("State : Dadra and Nagar Haveli\n\n"); }
			else if (s1.substr(0, 2) == "dd") { printf("State : Daman and Diu\n\n"); }
			else if (s1.substr(0, 2) == "dl") { printf("State : Delhi\n\n"); }
			else if (s1.substr(0, 2) == "ga") { printf("State : Goa\n\n"); }
			else if (s1.substr(0, 2) == "gj") { printf("State : Gujarat\n\n"); }
			else if (s1.substr(0, 2) == "hr") { printf("State : Haryana\n\n"); }
			else if (s1.substr(0, 2) == "hp") { printf("State : Himachal Pradesh\n\n"); }
			else if (s1.substr(0, 2) == "jk") { printf("State : Jammu and Kashmir\n\n"); }
			else if (s1.substr(0, 2) == "ka") { printf("State : Karnataka\n\n"); }
			else if (s1.substr(0, 2) == "kl") { printf("State : Kerala\n\n"); }
			else if (s1.substr(0, 2) == "ld") { printf("State : Lakshadweep\n\n"); }
			else if (s1.substr(0, 2) == "mp") { printf("State : Madhya Pradesh\n\n"); }
			else if (s1.substr(0, 2) == "mh") { printf("State : Maharashtra\n\n"); }
			else if (s1.substr(0, 2) == "mn") { printf("State : Manipur\n\n"); }
			else if (s1.substr(0, 2) == "ml") { printf("State : Meghalaya\n\n"); }
			else if (s1.substr(0, 2) == "mz") { printf("State : Mizoram\n\n"); }
			else if (s1.substr(0, 2) == "nl") { printf("State : Nagaland\n\n"); }
			else if (s1.substr(0, 2) == "or") { printf("State : Orissa\n\n"); }
			else if (s1.substr(0, 2) == "py") { printf("State : Pondicherry\n\n"); }
			else if (s1.substr(0, 2) == "pn") { printf("State : Punjab\n\n"); }
			else if (s1.substr(0, 2) == "rj") { printf("State : Rajasthan\n\n"); }
			else if (s1.substr(0, 2) == "sk") { printf("State : Sikkim\n\n"); }
			else if (s1.substr(0, 2) == "tn") { printf("State : TamilNadu\n\n"); }
			else if (s1.substr(0, 2) == "tr") { printf("State : Tripura\n\n"); }
			else if (s1.substr(0, 2) == "up") { printf("State : Uttar Pradesh\n\n"); }
			else if (s1.substr(0, 2) == "wb") { printf("State : West Bangal\n\n"); }
			else { cout << "Error due to unclear image."; }

			

			
			
			
			// Destroy used object and release memory because it will run again and again soo releasing this unwanted memory alocation is a good idea
			api->End(); // ending the api used
			delete api; //deleting it from used space
			delete[] outText; //also the extracted text 
			pixDestroy(&image); // Also distroy the binary image
		}
		
		
		imshow("Image", img);
		

		waitKey(1);//took a random delay by try and error 
		
		

	}
	return 0;
	
}