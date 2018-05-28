## Crack Detection 
-----------------    
-----------------   
                                    
<div style="text-align: right"> Planys Technologies </div>

### Crack Detection using Neural Network uses a Neural Network trained with crack images for identifying and classifying cracks from images.

### The network used here is the famous AlexNet which won the 2012 ImageNet LSVRC-2012 competition by a large margin in error rate for image classification.

## Training The Model

Training the model is the most crucial part of crack detection.

### Data Preparation

For Training the model, The training and validation data has to be chosen. This data should be labelled according the the expected output.

Caffe is used for building and training the model. Mode details on caffe framework can be found [here](http://caffe.berkeleyvision.org/).

Building and training the model has steps.

### 1. Building the Model
    
Since we are using the Alexnet, we download the .prototext files directly. Alexnet is used because its the right candidate for simple crack detection and training will be faster because of the small network size and number of parameters.

The other alternatives are [LeNet(Google)](http://deeplearning.net/tag/googlenet/)

### 2. Preparing Data

Training data should resemble the data with which we would be using the model. There will be two kinds of data
1. Training data
2. Validating data

training dataset will be bigger and will be used for training the model by recalculating each weights. 
Validation data will be used to check the status of training after a specified number of iterations.

Dividing the total data interms of 9 : 1 for training and validation will be enough.

data has to be prepared according to imagenet document given in caffe instructions

### 3. Training

After the data is converted into caffe readable database, the training can happen.

 The importnce of validation data set is that we use this dataset to determin when the model converged or to avoid overfitting(the model being overconstrained so that it will work on only training data and no other data).

Over the training period, the training accuracy will decrease because the model weight get recalculated and it get trained. Validation loss also will fall in starting phase since the model is getting better. However we can expect an increase in validation loss as the training continues. This indicates the the model is getting overfitted with training data. We stop the training at this stage when both training and validation loss is at the minimum.

Caffe training configuration file can be edited for training parameters such as number of iterations, number of iterations between tests, intermediate output file writing frequency.

After training, all the weights data will be written to .caffemodel file which is used to run the crack detection program.

.solverstate(file which get saved along with .caffemodel file) can be used for continueing the training if the training get inturruped.


## Running The Model

Running or using the pretrained model is simple.
1. Build the model

    ``` 
    cd build
    cmake ..
    make
    cd ..
    ```
2. Execute the code

    ```
    cd bin
    ./CrackDetection <path to image>
    ```

The output will contain output from network, and the confidence of that output.

Model output : 

    1 : No crack identified
    2 : Crack identified