import matplotlib.pyplot as plt
import rasterio
import numpy as np


lab, homework = 'lab-dem.tif', 'homework-dem.tif'

with rasterio.open(lab) as ds:
    lab_dem = ds.read(1)

with rasterio.open(homework) as ds:
    hw_dem = ds.read(1)

lab_dem[lab_dem == -32767] = np.nan
hw_dem[hw_dem == -32767] = np.nan

fig, axs = plt.subplots(1, 2, figsize=(12, 5))

min_pct, max_pct = 0.25, 99.75
lab_vmin, lab_vmax = np.nanpercentile(lab_dem, min_pct), np.nanpercentile(lab_dem, max_pct)
hw_vmin, hw_vmax = np.nanpercentile(hw_dem, min_pct), np.nanpercentile(hw_dem, max_pct)

lab_ax = axs[0].imshow(lab_dem, cmap='gray', vmin=lab_vmin, vmax=lab_vmax)
axs[0].set_title('Lab DEM')
axs[0].axis('off')
fig.colorbar(lab_ax, ax=axs[0], label='Elevation (m)', orientation='vertical', shrink=0.8)

hw_ax = axs[1].imshow(hw_dem, cmap='gray', vmin=hw_vmin, vmax=hw_vmax)
axs[1].set_title('Homework DEM')
axs[1].axis('off')
fig.colorbar(hw_ax, ax=axs[1], label='Elevation (m)', orientation='vertical', shrink=0.8)

plt.show()
