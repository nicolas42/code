# usage: python demo/run-on-video.py
# remove the following line to run on GPU
# cfg.MODEL.DEVICE = 'cpu'

input_filename = 'data/GH010042.MP4'
GUI = True
GPU = False

import os
os.environ['KMP_DUPLICATE_LIB_OK']='True'

import detectron2
from detectron2.utils.logger import setup_logger
setup_logger()

# import some common libraries
import numpy as np
import cv2
import matplotlib.pyplot as plt

# import some common detectron2 utilities
from detectron2 import model_zoo
from detectron2.engine import DefaultPredictor
from detectron2.config import get_cfg
from detectron2.utils.visualizer import Visualizer
from detectron2.data import MetadataCatalog

# register data-set
import os
import numpy as np
import json
from detectron2.structures import BoxMode
import random

def get_cane_dicts(directory):
    classes = ['cane', 'crown']
    dataset_dicts = []
    for filename in [file for file in os.listdir(directory) if file.endswith('.json')]:
        json_file = os.path.join(directory, filename)
        with open(json_file) as f:
            img_anns = json.load(f)	
        record = {}
        filename = os.path.join(directory, img_anns["imagePath"])
        record["file_name"] = filename
        record["height"] = 1440
        record["width"] = 1920
        annos = img_anns["shapes"]
        objs = []
        for anno in annos:
            px = [a[0] for a in anno['points']]
            py = [a[1] for a in anno['points']]
            poly = [(x, y) for x, y in zip(px, py)]
            poly = [p for x in poly for p in x]

            obj = {
                "bbox": [np.min(px), np.min(py), np.max(px), np.max(py)],
                "bbox_mode": BoxMode.XYXY_ABS,
                "segmentation": [poly],
                "category_id": classes.index(anno['label']),
                "iscrowd": 0
            }
            objs.append(obj)
        record["annotations"] = objs
        dataset_dicts.append(record)
    return dataset_dicts

from detectron2.data import DatasetCatalog, MetadataCatalog
for d in ["train", "test"]:
    DatasetCatalog.register("cane_" + d, lambda d=d: get_cane_dicts('bitwise-segmentation/' + d))
    MetadataCatalog.get("cane_" + d).set(thing_classes=['cane', 'crown'])
cane_metadata = MetadataCatalog.get("cane_train")



# configure net
from detectron2.engine import DefaultTrainer
from detectron2.config import get_cfg

cfg = get_cfg()
cfg.merge_from_file(model_zoo.get_config_file("COCO-InstanceSegmentation/mask_rcnn_R_50_FPN_3x.yaml"))
cfg.DATASETS.TRAIN = ("cane_train",)
cfg.DATASETS.TEST = ()
cfg.DATALOADER.NUM_WORKERS = 2
cfg.MODEL.WEIGHTS = model_zoo.get_checkpoint_url("COCO-InstanceSegmentation/mask_rcnn_R_50_FPN_3x.yaml")
cfg.SOLVER.IMS_PER_BATCH = 2
cfg.SOLVER.BASE_LR = 0.00025
cfg.SOLVER.MAX_ITER = 1000
cfg.MODEL.ROI_HEADS.NUM_CLASSES = 4
if not GPU:
    cfg.MODEL.DEVICE = 'cpu'

# inference

cfg.MODEL.WEIGHTS = os.path.join(cfg.OUTPUT_DIR, "model_final.pth")
cfg.MODEL.ROI_HEADS.SCORE_THRESH_TEST = 0.5
cfg.DATASETS.TEST = ("cane_test", )
predictor = DefaultPredictor(cfg)



from detectron2.utils.visualizer import ColorMode
dataset_dicts = get_cane_dicts('bitwise-segmentation/test')



##################################################################


import cv2
import numpy as np

vidcap = cv2.VideoCapture(input_filename)
success,img = vidcap.read()
count = 0
success = True
successive_failures = 0

scale_percent = 50 # percent of original size
width = int(img.shape[1] * scale_percent / 100)
height = int(img.shape[0] * scale_percent / 100)
dim = (width, height)
fourcc = cv2.VideoWriter_fourcc(*'XVID')
out = cv2.VideoWriter('output.avi',fourcc, 20.0, (width,height))

while successive_failures < 10:
    success,img = vidcap.read()
    if not success:
        successive_failures += 1
        print('¯\_(ツ)_/¯')
        continue
    else:
        successive_failures = 0

    scale_percent = 50 # percent of original size
    width = int(img.shape[1] * scale_percent / 100)
    height = int(img.shape[0] * scale_percent / 100)
    dim = (width, height)
    # resize img
    img = cv2.resize(img, dim, interpolation = cv2.INTER_AREA)


    # im = cv2.imread(d["file_name"])
    outputs = predictor(img)
    v = Visualizer(img[:, :, ::-1],
                   metadata=cane_metadata, 
                   scale=0.8, 
                   instance_mode=ColorMode.IMAGE_BW   # remove the colors of unsegmented pixels
    )
    v = v.draw_instance_predictions(outputs["instances"].to("cpu"))
    img_inference = cv2.cvtColor(v.get_image()[:, :, ::-1], cv2.COLOR_BGR2RGB)
    # cv2.imwrite('test.jpg', img_inference)
    if GUI:
        cv2.imshow('output',img_inference)
    out.write(img_inference)


    #   cv2.imwrite("frame%d.jpg" % count, img)     # save frame as JPEG file
    # cv2.imshow('output',img_inference)

    # kernel = np.ones((10,10), np.uint8)
    # kernel = cv2.getStructuringElement(cv2.MORPH_ELLIPSE,(10,10))

    # img_erosion = cv2.erode(img, kernel, iterations=1)
    # img_dilation = cv2.dilate(img, kernel, iterations=1)

    # #   cv2.imwrite("frame%d.jpg" % count, img)     # save frame as JPEG file
    # cv2.imshow('output',img_dilation)

    # out.write(img_dilation)
    # try:
    #     cv2.imshow('output',img)
    # except:
    #     print('opencv thinks this is a sad frame')

    if GUI:    
        if cv2.waitKey(10) == 27:                     # exit if Escape is hit
            break
    count += 1



vidcap.release()
out.release()
if GUI:
    cv2.destroyAllWindows()
