import matplotlib.image as mimg
import numpy as np
import matplotlib.pyplot as plt
from os import listdir
import scipy.misc
import skimage.io as sio
from pydicom import dcmread, errors

import imageio as iio
import cv2



def negate_number(number):
    return 1.0 - number if type(number) is np.float32 else 255 - number


def mirror_image(image):
    height = len(image) - 1
    width = len(image[0]) - 1
    for height_counter in range(height):
        for width_counter in range(int(width / 2)):
            image[height_counter][width_counter], image[height_counter][width - width_counter] = image[height_counter][width - width_counter], image[height_counter][width_counter]
    return np.array(image, dtype=np.uint8)


def show_images_plt(img1, img2):
    f = plt.figure()
    f.add_subplot(1, 2, 1)
    plt.imshow(np.rot90(img1, 0))
    f.add_subplot(1, 2, 2)
    plt.imshow(np.rot90(img2, 0))
    plt.show(block=True)


def show_images_cv2(img1, img2):
    cv2.imshow('Frame1', img1)
    cv2.imshow('Frame2', img2)
    cv2.waitKey(0)
    cv2.destroyAllWindows()


def zad1():
    files = listdir('input1')
    for file in files:
        open_file = mimg.imread(r'input1/{}'.format(file))
        plt.imshow(open_file)
        # Metoda Roberta
        invert_colors = open_file.tolist()
        for row_count, row in enumerate(open_file):
            for data_count, data in enumerate(row):
                invert_colors[row_count][data_count][0] = negate_number(open_file[row_count][data_count][0])
                invert_colors[row_count][data_count][1] = negate_number(open_file[row_count][data_count][1])
                invert_colors[row_count][data_count][2] = negate_number(open_file[row_count][data_count][2])
        invert_colors = np.array(invert_colors)
        # Metoda student_pro!!
        # invert_colors = 1 - open_file
        plt.imshow(invert_colors)
        plt.show()
        name, ext = file.split('.')
        scipy.misc.imsave(r"output/{}_2.{}".format(name, ext), invert_colors)


def zad2():
    files = listdir('input1')
    for file in files:
        open_file = sio.imread(r'input1/{}'.format(file))
        invert_mirror = mirror_image(open_file.tolist())
        show_images_plt(open_file, invert_mirror)
        name, ext = file.split('.')
        iio.imsave(r"output/{}_3.{}".format(name, ext), invert_mirror)


def zad3():
    files = listdir('input1')
    for file in files:
        open_file = cv2.imread('input1/{}'.format(file), 1)
        if open_file is None: # Pliki .GIF nie są wspierane
            continue
        invert_mirror = mirror_image(open_file.tolist())
       # show_images_cv2(open_file, invert_mirror)
        name, ext = file.split('.')
        cv2.imwrite(r"output/{}_4.{}".format(name, ext),
        cv2.cvtColor(invert_mirror, cv2.COLOR_RGB2GRAY))


def zad4():
    files = listdir('input2')
    for file in files:
        try:
            open_file = dcmread('input2/{}'.format(file), 1)
        except errors.InvalidDicomError:
            print('File "%s" is not dcm file' % (file))
            continue
        print(open_file)
        bit_size = open_file.BitsStored
        open_file = open_file.pixel_array
        is_3d = type(open_file[0][0]) is np.ndarray
        x, y, z = len(open_file), len(open_file[0]), len(open_file[0][0]) if is_3d else None
        print(is_3d, x, y, z, bit_size)
        # Małe info: Nagłówki to są wszystkie atrybuty obiektu DICOM, nie widzę sensu ich wszystkich wypisywać


def zad5():
    collection = sio.ImageCollection(r'fluo-series/*')
    sio.imshow_collection(collection)
    list_collection = list(collection)
    for image_count, image in enumerate(collection):
        list_collection[image_count] = np.transpose(image)
    sio.imshow_collection(list_collection)
    tif_file = sio.imread(r'input2/multipage_rgb.tif')
    print('Wymiary: ' + str(tif_file.shape))
    print('Typ: ' + str(type(tif_file[0][0][0][0])))
    # Aby zamienić typ wystarczy iterować całą tablicę i zmienić type na uint8 funkcją z polecenia


def calc_sr(lista, y_offset, x_offset, byte):
    sr = 0
    for y in range(-1, 2):
        for x in range(-1, 2):
            try:
                sr += lista[y_offset + y][x_offset + x][byte]
            except IndexError:
                return lista[y_offset][x_offset][byte]
    return sr / 9

def somsiad_filter(image):
    filter_effect = list(image)
    for row_count, row in enumerate(image):
        for data_count, data in enumerate(row):
            for byte_count, byte in enumerate(data):
                filter_effect[row_count][data_count][byte_count] = calc_sr(filter_effect, row_count, data_count, byte_count)
    return np.array(filter_effect)


def kolos():
    # Otwarcie i wyświetlenie obrazu
    open_file = mimg.imread('lena.png')
    plt.imshow(open_file)
    plt.show()

    # Histogram - Na osi Y - Ile danych wartości znalazło się na bitach, na osi x - te oto wartości
    # Argument od lewej: Plik, krok wyliczenia X (pozmieniaj sobie i zobacz), zakres danych, zmiana koloru bloków na wykresie
    plt.hist(open_file.flatten(), 10, range=(0.0, 1.0), fc='k')
    plt.show()

    # Rozjaśnienie obrazu
    lighter_file = np.clip(open_file + 0.2, 0, 1)  # Funkcja clip ustawia max i min w całej tablicy.
    plt.imshow(lighter_file)
    plt.show()

    # Przyciemnienie obrazu
    darker_file = np.clip(open_file - 0.2, 0, 1)
    plt.imshow(darker_file)
    plt.show()

    # Nałożenie szumu. Aby zwiększyć szum pobawcie się ostatnim dzieleniem i odejmowaniem
    szum = np.random.randn(len(open_file), len(open_file[0]), 3) / 10 - 0.05
    szum_file = np.clip(open_file + szum, 0, 1)
    plt.imshow(szum_file)
    plt.show()
    filtered_file = somsiad_filter(open_file)
    plt.imshow(filtered_file)
    plt.show()

    # Konwersja obrazu i zapis
    scipy.misc.imsave('lena.jpg', open_file)

kolos()
