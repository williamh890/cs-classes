import matplotlib.pyplot as plt
import rasterio
import numpy as np


def plot_dems():
    lab, homework = 'lab-dem.tif', 'homework-dem.tif'

    with rasterio.open(lab) as ds:
        lab_dem = ds.read(1)

    with rasterio.open(homework) as ds:
        hw_dem = ds.read(1)

    lab_dem[lab_dem == -32767] = np.nan
    hw_dem[hw_dem == -32767] = np.nan

    fig, axs = plt.subplots(1, 3, figsize=(12, 5))

    axs[0].imshow(lab_dem, cmap='gray')
    axs[0].set_title('Lab DEM')
    axs[0].axis('off')

    axs[1].imshow(hw_dem, cmap='gray')
    axs[1].set_title('Homework DEM')
    axs[1].axis('off')

    min_h = min(lab_dem.shape[0], hw_dem.shape[0])
    min_w = min(lab_dem.shape[1], hw_dem.shape[1])

    lab_dem = lab_dem[:min_h, :min_w]
    hw_dem = hw_dem[:min_h, :min_w]

    diff = lab_dem - hw_dem
    axs[2].imshow(diff, cmap='gray')
    axs[2].set_title('Difference (lab - hw)')
    axs[2].axis('off')

    print(f'mean: {np.nanmean(diff)}, std: {np.nanstd(diff)}')

    plt.show()


if __name__ == '__main__':
    plot_dems()
