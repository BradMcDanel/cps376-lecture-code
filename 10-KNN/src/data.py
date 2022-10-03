from torchvision.datasets import MNIST

train = MNIST("../data", train=True, download=True)
test = MNIST("../data", train=False, download=True)

output_path = "../data/mnist_images/"

# output png images for each sample
for i in range(len(train)):
    img, label = train[i]
    img.save(output_path + "train/" + str(i) + ".png")

# output labels to output_path + "train_labels.txt"
with open(output_path + "train_labels.txt", "w") as f:
    for i in range(len(train)):
        _, label = train[i]
        f.write(str(label) + "\n")

for i in range(len(test)):
    img, label = test[i]
    img.save(output_path + "test/" + str(i) + ".png")

# output labels to output_path + "test_labels.txt"
with open(output_path + "test_labels.txt", "w") as f:
    for i in range(len(test)):
        _, label = test[i]
        f.write(str(label) + "\n")
