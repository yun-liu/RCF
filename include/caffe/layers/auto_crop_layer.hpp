#ifndef CAFFE_AUTO_CROP_LAYER_HPP_
#define CAFFE_AUTO_CROP_LAYER_HPP_

#include <utility>
#include <vector>

#include "caffe/blob.hpp"
#include "caffe/layer.hpp"
#include "caffe/proto/caffe.pb.h"

namespace caffe {

/**
 * @brief Takes a Blob and crop it, to the shape specified by the second input
 *  Blob, across all dimensions after the specified axis.
 *
 * TODO(dox): thorough documentation for Forward, Backward, and proto params.
 */
 template <typename Dtype>
 class AutoCropLayer : public Layer<Dtype> {
  public:
   explicit AutoCropLayer(const LayerParameter& param)
       : Layer<Dtype>(param) {}
   virtual void LayerSetUp(const vector<Blob<Dtype>*>& bottom,
       const vector<Blob<Dtype>*>& top);
   virtual void Reshape(const vector<Blob<Dtype>*>& bottom,
       const vector<Blob<Dtype>*>& top);

   virtual inline const char* type() const { return "AutoCrop"; }
   virtual inline int ExactNumBottomBlobs() const { return 2; }
   virtual inline int ExactNumTopBlobs() const { return 1; }

   virtual inline DiagonalAffineMap<Dtype> coord_map() {
     vector<pair<Dtype, Dtype> > coefs;
     coefs.push_back(make_pair(1, - crop_h_));
     coefs.push_back(make_pair(1, - crop_w_));
     return DiagonalAffineMap<Dtype>(coefs);
   }

  protected:
   virtual void Forward_cpu(const vector<Blob<Dtype>*>& bottom,
       const vector<Blob<Dtype>*>& top);
   virtual void Backward_cpu(const vector<Blob<Dtype>*>& top,
       const vector<bool>& propagate_down, const vector<Blob<Dtype>*>& bottom);
   virtual void Forward_gpu(const vector<Blob<Dtype>*>& bottom,
       const vector<Blob<Dtype>*>& top);
   virtual void Backward_gpu(const vector<Blob<Dtype>*>& top,
       const vector<bool>& propagate_down, const vector<Blob<Dtype>*>& bottom);

   int crop_h_, crop_w_;
 };

}  // namespace caffe

#endif  // CAFFE_AUTO_CROP_LAYER_HPP_
