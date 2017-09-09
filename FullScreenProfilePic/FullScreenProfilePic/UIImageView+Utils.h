#import <UIKit/UIKit.h>

@interface UIImageView (Utils)<UIGestureRecognizerDelegate,UIScrollViewDelegate>

@property(nonatomic,strong)UIImageView *fullimageview;
@property(nonatomic,strong)UIImageView *temptumb;
@property(nonatomic,strong)UIScrollView *scrlView;
@property(nonatomic,strong)UIView *viewbg;
@property(nonatomic,strong)UIView *view;
@property(nonatomic,strong)NSNumber *xPos;
@property(nonatomic,strong)NSNumber *yPos;


// METHOD FOR INITILIZE
-(void)methodPhotoViewerWithSuperView:(UIView *)view;

@end
