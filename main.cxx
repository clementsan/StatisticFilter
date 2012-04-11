#include <iostream>

#include <itkImage.h>
#include <itkImageFileReader.h> 
#include <itkImageFileWriter.h>
#include <itkNeighborhoodIterator.h>
#include <itkImageRegionIterator.h>
#include <itkImageRegionConstIterator.h>

using namespace itk;
using namespace std;

const int Dimension = 3;
typedef unsigned short ImagePixelType;
typedef Image<ImagePixelType,Dimension>  ImageType;

typedef ImageFileReader<ImageType> VolumeReaderType;
typedef ImageFileWriter<ImageType> VolumeWriterType;
typedef NeighborhoodIterator<ImageType> NeighborhoodIteratorType;
typedef ImageRegionIterator<ImageType> IteratorType;
typedef ImageRegionConstIterator<ImageType> ConstIteratorType;

int main(int argc, const char* argv[])
{
  ImageType::Pointer inputImage;
  VolumeReaderType::Pointer labelReader = VolumeReaderType::New();

  // Reading input Image
  VolumeReaderType::Pointer imageReader = VolumeReaderType::New();
  imageReader->SetFileName(argv[1]) ;
  try
    {
      imageReader->Update() ;
    }
  catch (ExceptionObject err)
    {
      cerr<<"Exception object caught!"<<std::endl;
      cerr<<err<<std::endl;
      exit(0) ;
    }
  inputImage = imageReader->GetOutput();

  // Creating output image
  ImageType::Pointer OutputImage = ImageType::New();
  OutputImage->SetRegions(inputImage->GetRequestedRegion());
  OutputImage->Allocate();

  ConstIteratorType ConstInputIterator(inputImage,inputImage->GetRequestedRegion());
  IteratorType OutputIterator(OutputImage, inputImage->GetRequestedRegion());
    
  NeighborhoodIteratorType::RadiusType Radius;
  Radius.Fill(1);
  NeighborhoodIteratorType NeighborhoodInputIterator(Radius,inputImage,inputImage->GetRequestedRegion());
  NeighborhoodIteratorType::OffsetType offset1 = {{-1,-1,-1}};
  NeighborhoodIteratorType::OffsetType offset2 = {{-1,-1,0}};
  NeighborhoodIteratorType::OffsetType offset3 = {{-1,-1,1}};
  NeighborhoodIteratorType::OffsetType offset4 = {{-1,0,-1}};
  NeighborhoodIteratorType::OffsetType offset5 = {{-1,0,0}};
  NeighborhoodIteratorType::OffsetType offset6 = {{-1,0,1}};
  NeighborhoodIteratorType::OffsetType offset7 = {{-1,1,-1}};
  NeighborhoodIteratorType::OffsetType offset8 = {{-1,1,0}};
  NeighborhoodIteratorType::OffsetType offset9 = {{-1,1,1}};
  
  NeighborhoodIteratorType::OffsetType offset10 = {{0,-1,-1}};
  NeighborhoodIteratorType::OffsetType offset11 = {{0,-1,0}};
  NeighborhoodIteratorType::OffsetType offset12 = {{0,-1,1}};
  NeighborhoodIteratorType::OffsetType offset13 = {{0,0,-1}};
  NeighborhoodIteratorType::OffsetType offset14 = {{0,0,1}};
  NeighborhoodIteratorType::OffsetType offset15 = {{0,1,-1}};
  NeighborhoodIteratorType::OffsetType offset16 = {{0,1,0}};
  NeighborhoodIteratorType::OffsetType offset17 = {{0,1,1}};
  
  NeighborhoodIteratorType::OffsetType offset18 = {{1,-1,-1}};
  NeighborhoodIteratorType::OffsetType offset19 = {{1,-1,0}};
  NeighborhoodIteratorType::OffsetType offset20 = {{1,-1,1}};
  NeighborhoodIteratorType::OffsetType offset21 = {{1,0,-1}};
  NeighborhoodIteratorType::OffsetType offset22 = {{1,0,0}};
  NeighborhoodIteratorType::OffsetType offset23 = {{1,0,1}};
  NeighborhoodIteratorType::OffsetType offset24 = {{1,1,-1}};
  NeighborhoodIteratorType::OffsetType offset25 = {{1,1,0}};
  NeighborhoodIteratorType::OffsetType offset26 = {{1,1,1}};
 
  // Computation
  // -  Copy input data to output
  for (ConstInputIterator.GoToBegin(), OutputIterator.GoToBegin(); !ConstInputIterator.IsAtEnd(); \
       ++ConstInputIterator, ++OutputIterator)
    OutputIterator.Set(ConstInputIterator.Get());
      
  ImagePixelType sum;
  OutputIterator.GoToBegin();
  NeighborhoodInputIterator.GoToBegin();
  while (!OutputIterator.IsAtEnd())
      {
	sum = NeighborhoodInputIterator.GetPixel(offset1)+NeighborhoodInputIterator.GetPixel(offset2)+\
	  NeighborhoodInputIterator.GetPixel(offset3)+NeighborhoodInputIterator.GetPixel(offset4)+ \
	  NeighborhoodInputIterator.GetPixel(offset5)+NeighborhoodInputIterator.GetPixel(offset6)+ \
	  NeighborhoodInputIterator.GetPixel(offset7)+NeighborhoodInputIterator.GetPixel(offset8)+ \
	  NeighborhoodInputIterator.GetPixel(offset9)+NeighborhoodInputIterator.GetPixel(offset10)+ \
	  NeighborhoodInputIterator.GetPixel(offset11)+NeighborhoodInputIterator.GetPixel(offset12)+ \
	  NeighborhoodInputIterator.GetPixel(offset13)+NeighborhoodInputIterator.GetPixel(offset14)+ \
	  NeighborhoodInputIterator.GetPixel(offset15)+NeighborhoodInputIterator.GetPixel(offset16)+ \
	  NeighborhoodInputIterator.GetPixel(offset17)+NeighborhoodInputIterator.GetPixel(offset18)+ \
	  NeighborhoodInputIterator.GetPixel(offset19)+NeighborhoodInputIterator.GetPixel(offset20)+ \
	  NeighborhoodInputIterator.GetPixel(offset21)+NeighborhoodInputIterator.GetPixel(offset22)+ \
	  NeighborhoodInputIterator.GetPixel(offset23)+NeighborhoodInputIterator.GetPixel(offset24)+ \
	  NeighborhoodInputIterator.GetPixel(offset25)+NeighborhoodInputIterator.GetPixel(offset26);
	if ( (NeighborhoodInputIterator.GetCenterPixel() == 0) && (sum > 17) )
	  OutputIterator.Set(1);
	else if ( (NeighborhoodInputIterator.GetCenterPixel() == 1) && (sum < 9) )
	  OutputIterator.Set(0);
	++OutputIterator;
	++NeighborhoodInputIterator;
      }


  VolumeWriterType::Pointer writer = VolumeWriterType::New();
  writer->SetFileName(argv[2]);
  writer->SetInput(OutputImage);
  try
    {
      writer->Update();
    }
  catch (itk::ExceptionObject & err)
    {
      std::cerr<<"Exception object caught!"<<std::endl;
	std::cerr<<err<<std::endl;
    }
  return EXIT_SUCCESS;
}
