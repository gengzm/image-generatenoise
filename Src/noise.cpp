#include<opencv2/opencv.hpp>
#include<random>

cv::Mat salt(cv::Mat src, int noise_num)
{
    int i, j;
    cv::Mat image = src.clone();
    const char value = 255;
    if (image.type() == CV_8UC1)
    {
        for (int k = 0; k < noise_num; k++) {
            // rand() is the random number generator
            i = std::rand() % image.cols; // % 整除取余数运算符,rand=1022,cols=1000,rand%cols=22
            j = std::rand() % image.rows;
            image.at<uchar>(j, i) = value; //at方法需要指定Mat变量返回值类型,如uchar等
        }
    }
    else if (image.type() == CV_8UC3)
    { // color image
        for (int k = 0; k < noise_num; k++) {
            // rand() is the random number generator
            i = std::rand() % image.cols; // % 整除取余数运算符,rand=1022,cols=1000,rand%cols=22
            j = std::rand() % image.rows;

            image.at<cv::Vec3b>(j, i)[0] = value; //cv::Vec3b为opencv定义的一个3个值的向量类型
            image.at<cv::Vec3b>(j, i)[1] = value; //[]指定通道，B:0，G:1，R:2
            image.at<cv::Vec3b>(j, i)[2] = value;
        }
    }

    return image;
}

cv::Mat pepper(cv::Mat src, int noise_num, uint32_t noise_size = 1)
{
    int i, j;
    cv::Mat image = src.clone();
    const char value = 0;
    std::random_device rd;
    std::default_random_engine e(rd());
    std::uniform_int_distribution<> u;
    if (image.type() == CV_8UC1)
    {
        for (int k = 0; k < noise_num; k++) {
            // rand() is the random number generator
            i = u(e) % (image.cols - noise_size); // % 整除取余数运算符,rand=1022,cols=1000,rand%cols=22
            j = u(e) % (image.rows - noise_size);
            for (int y = 0; y < noise_size; y++)
            {
                for (int x = 0; x < noise_size; x++)
                {
                    image.at<uchar>(j+y, i+x) = value; //at方法需要指定Mat变量返回值类型,如uchar等
                }
                
            }
        }
    }
    else if (image.type() == CV_8UC3)
    { // color image
        for (int k = 0; k < noise_num; k++) {
            // rand() is the random number generator
            i = u(e) % (image.cols - noise_size); // % 整除取余数运算符,rand=1022,cols=1000,rand%cols=22
            j = u(e) % (image.rows - noise_size);

            for (int y = 0; y < noise_size; y++)
            {
                for (int x = 0; x < noise_size; x++)
                {
                    image.at<cv::Vec3b>(j+y, i+x)[0] = value; //cv::Vec3b为opencv定义的一个3个值的向量类型
                    image.at<cv::Vec3b>(j+y, i+x)[1] = value; //[]指定通道，B:0，G:1，R:2
                    image.at<cv::Vec3b>(j+y, i+x)[2] = value;
                }

            }
            
        }
    }
     
    return image;
}

void copy()
{
    const std::string path = "C:/Temp/colorimage.bmp";
    cv::Mat src = cv::imread(path, cv::IMREAD_COLOR);

    cv::Mat dst1;
    cv::Mat dst2;

    std::vector<double> ratios;
    std::cout << "start:";
    const int num = 100000;
    for (int i = 0; i < num; i++)
    {
        double t = cv::getTickCount();
        dst1 = src.clone();
        t = (cv::getTickCount() - t);
        //std::cout << "clone:" << t << std::endl;

        double t1 = cv::getTickCount();
        src.copyTo(dst2);
        t1 = (cv::getTickCount() - t1);
        //std::cout << "copyTo:" << t1 << std::endl;

        double r = t / t1;
        ratios.push_back(r);
        //std::cout << "clone-CopytTo Ratio: " << r << std::endl;
        //std::cout << "--------------------------------\n";
        if (i % 10 == 0)
        {
            std::cout << i << "/" << num << std::endl;
        }
    }
    std::cout << "copyTo:" << ratios[0] << std::endl;
    
    system("pause");
    
}

void c3toc1()
{
    //cv::Mat mat2 = cv::imread("C:/Temp/calibration/boundary.bmp", CV_LOAD_IMAGE_GRAYSCALE);
    //cv::imwrite("C:/Temp/calibration/boundary-gray.bmp", mat2);
}

void genpepper()
{
    for (int i = 0; i < 20; i++)
    {
        cv::Mat mat = cv::Mat(4000, 4000, CV_8UC3, cv::Scalar(255, 255, 255));
        cv::Mat noise = pepper(mat, mat.cols * mat.rows /( (i+1)*(i+1) * 3 ) , i+1 );
        cv::Mat rs;
        cv::resize(noise, rs, cv::Size(mat.cols * 3, mat.rows * 3));
        cv::Mat noise2 = rs;// pepper(rs, rs.cols * rs.rows / 10);
        char str[100];
        sprintf(str, "4000_size%d", (i + 1) );
        cv::putText(noise, str, cv::Point(mat.cols * 0.7,mat.rows*0.7), cv::FONT_HERSHEY_PLAIN, 6, cv::Scalar(20,20,120), 2);
        sprintf(str, "C:/Temp/noise.bmp4000_%d.bmp", i);
        cv::imwrite(str, noise);
        std::cout << (str) << std::endl;
    }
}

int main ()
{
    genpepper();
    return 0;
}