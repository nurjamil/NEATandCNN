# NEATandCNN
NEAT and CNN Implementation in C++
CNN
 ```bash
  InputFile in;
  in.LoadFromOneFolder(//Your Test / Train Folder Path//);
  
  convolution_layer *CNN = nullptr;
  //initialize CNN
	CNN = new convolution_layer(0.0005, 0.99, false);
	CNN->addLayer1(5,16, Layer_type::convoluteRelu);
	CNN->addLayer3(Layer_type::maxPool);
	CNN->addLayer1(3,32, Layer_type::convoluteRelu);
	CNN->addLayer3(Layer_type::maxPool);
	CNN->addLayer3(Layer_type::flatten);
	CNN->addLayer2(128, Layer_type::fullyConn);
	CNN->addLayer2(8, Layer_type::fullyConnSoftmax);
  
  CNN->training(in.inputD,//batchsize,false);
  ```
 
 
 NEAT
  ```bash
  PrepareInput in;
  in.LoadFromOneFolder(//Your Test / Train Folder Path//);
  
  NEAT *neat = nullptr;
  neat = new NEAT(784, 20, 8, 20);
  ```
 


