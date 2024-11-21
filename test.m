Sobel('/home/zk18l/Downloads/WebDownloads/test.jpg');

function Sobel(im)
    % Read in the image and convert to gray
    orig = imread(im);
    grayscale = rgb2gray(orig);

    % Define the Sobel kernels
    k_v = [-1 0 1; -2 0 2; -1 0 1]; % Vertical kernel
    k_h = [1 2 1; 0 0 0; -1 -2 -1]; % Horizontal kernel

    % Convolve the gray image with Sobel kernels
    M1 = conv2(double(grayscale), double(k_v), 'same'); % Vertical edges
    M2 = conv2(double(grayscale), double(k_h), 'same'); % Horizontal edges

    % Create one figure with subplots
    figure;

    % Original grayscale image
    subplot(2, 3, 2);
    imshow(grayscale);
    title('Grayscale Image');

    % Original image
    subplot(2, 3, 1);
    imshow(orig);
    title('Original Image');

    % Vertical edges
    subplot(2, 3, 3);
    imshow(abs(M1), []);
    title('Vertical Edges');

    % Horizontal edges
    subplot(2, 3, 4);
    imshow(abs(M2), []);
    title('Horizontal Edges');

    % Combined edges (gradient magnitude)
    subplot(2, 3, 5);
    imshow((M1.^2 + M2.^2).^0.5, []);
    title('Gradient Magnitude');

    % Optional: Add empty subplot for aesthetic spacing
    subplot(2, 3, 6);
    axis off; % Turn off the axis
    text(0.5, 0.5, 'Edge Detection', 'HorizontalAlignment', 'center');
end
