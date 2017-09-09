//
//  UIImageView+Utils.m
//  imageTap
//
//  Created by OWNER on 01/09/17.
//  Copyright © 2017 OWNER. All rights reserved.
//

#import "UIImageView+Utils.h"
#import <objc/runtime.h>
#define MINIMUM_SCALE 0.5
#define MAXIMUM_SCALE 6.0


@implementation UIImageView (Utils)

// SYSNTHESIZE PROPERTY
-(UIView *)viewbg{
    return objc_getAssociatedObject (self, @selector(viewbg));
}
-(void)setViewbg:(UIView *)viewbg{
    objc_setAssociatedObject(self, @selector(viewbg), viewbg, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}
-(UIView *)view{
    return objc_getAssociatedObject (self, @selector(view));
}
-(void)setView:(UIView *)view{
    objc_setAssociatedObject(self, @selector(view), view, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}

-(UIImageView *)fullimageview{
    return objc_getAssociatedObject (self, @selector(fullimageview));
}
-(void)setFullimageview:(UIImageView *)fullimageview{
    objc_setAssociatedObject(self, @selector(fullimageview), fullimageview, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}
-(UIScrollView *)scrlView{
    return objc_getAssociatedObject (self, @selector(scrlView));
}
-(void)setScrlView:(UIScrollView *)scrlView{
    objc_setAssociatedObject(self, @selector(scrlView), scrlView, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}
-(NSNumber *)xPos{
    return objc_getAssociatedObject (self, @selector(xPos));
}
-(NSNumber *)yPos{
    return objc_getAssociatedObject (self, @selector(yPos));
}
-(void)setXPos:(NSNumber *)xPos{
    objc_setAssociatedObject(self, @selector(xPos), xPos, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}
-(void)setYPos:(NSNumber *)yPos{
    objc_setAssociatedObject(self, @selector(yPos), yPos, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}
// SET PHOTO VIEWER
-(void)methodPhotoViewer{
    UIView *vw = [[[[UIApplication sharedApplication] keyWindow] subviews] lastObject];
    [self methodPhotoViewerWithSuperView:vw];
}
-(void)methodPhotoViewerWithSuperView:(UIView *)view{
    if (self.image == nil){
        return;
    }
    CGRect screenRect = [[UIScreen mainScreen] bounds];

    self.view = view;
    
    self.view.frame = CGRectMake(0, 0, screenRect.size.width, screenRect.size.height);
    
    // MAKE ON USER INTERCATINO ON
    [self setUserInteractionEnabled:YES];
    
    // ADD GESTURE
    UITapGestureRecognizer *gesture = [[UITapGestureRecognizer alloc]initWithTarget:self action:@selector(bannerTapped:)];
    gesture.numberOfTapsRequired = 1;
    gesture.cancelsTouchesInView = YES;
    [self addGestureRecognizer:gesture];
    
}

- (void)bannerTapped:(UIGestureRecognizer *)gestureRecognizer {
    NSLog(@"%@ %@", [gestureRecognizer view],self.view);
    CGRect screenRect = [[UIScreen mainScreen] bounds];
    CGPoint tapPoint = [gestureRecognizer locationInView:self.view];
    
    self.xPos = [NSNumber numberWithFloat:tapPoint.x];
    self.yPos = [NSNumber numberWithFloat:tapPoint.y];
    
    //create new image
//    self.temptumb=(UIImageView *)gestureRecognizer.view;
    //self.fullimageview is gloabal, So we can acess any time to remove it
    self.fullimageview=[[UIImageView alloc]init];
    [self.fullimageview setContentMode:UIViewContentModeScaleAspectFit];
    
    self.fullimageview.image = [(UIImageView *)gestureRecognizer.view image];
    
    // ADD PIN GESTURE
    UIPinchGestureRecognizer *pgr = [[UIPinchGestureRecognizer alloc]initWithTarget:self action:@selector(handlePinchGesture:)];
    pgr.delegate = self;
    [self.fullimageview addGestureRecognizer:pgr];

    // ADD SCRLVIEW DELEGATE
    self.scrlView = [[UIScrollView alloc] initWithFrame:CGRectMake(0, 0, screenRect.size.width, self.view.frame.size.height)];
    self.scrlView.minimumZoomScale = MINIMUM_SCALE;
    self.scrlView.maximumZoomScale = MAXIMUM_SCALE;
    self.scrlView.contentSize = self.fullimageview.frame.size;
    self.scrlView.delegate = self;
    
        NSLog(@"%@",self.view);
    // ADD TRANSPARANT BG
    self.viewbg = [[UIView alloc] initWithFrame:CGRectMake(0, 0, screenRect.size.width, self.view.frame.size.height)];
    self.viewbg.backgroundColor = [UIColor blackColor];//[UIColor colorWithPatternImage:self.temptumb.image];
    self.viewbg.alpha = 0.6;
    
    [self.view addSubview:self.viewbg];
    [self.scrlView addSubview:self.fullimageview];
    
    [self.view addSubview:self.scrlView];

    CGRect originalpoint=[self.view convertRect:self.bounds fromView:self];
    [self.fullimageview setFrame:originalpoint];
    [UIView animateWithDuration:0.5
                     animations:^{
                         
                         [self.fullimageview setFrame:CGRectMake(0,
                                                                 0,
                                                                 self.view.frame.size.width,
                                                                 self.view.frame.size.height)];
                     }];
    UITapGestureRecognizer *singleTap = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(fullimagetapped:)];
    singleTap.numberOfTapsRequired = 1;
    singleTap.numberOfTouchesRequired = 1;
    [self.fullimageview addGestureRecognizer:singleTap];
    [self.fullimageview setUserInteractionEnabled:YES];
}
-(void)fullimagetapped:(UIGestureRecognizer *)gestureRecognizer {
    CGRect originalpoint=[self.view convertRect:self.bounds fromView:self];

    
    gestureRecognizer.view.backgroundColor=[UIColor clearColor];
    [UIView animateWithDuration:0.5
                     animations:^{
                         [(UIImageView *)gestureRecognizer.view setFrame:originalpoint];
                     }];
   [self performSelector:@selector(animationDone:) withObject:[gestureRecognizer view] afterDelay:0.4];
}

-(void)handlePinchGesture:(UIPinchGestureRecognizer*)recognizer{
    if ([recognizer scale]<MINIMUM_SCALE) {
        NSLog(@"======== %f Scale Applied ===========",[recognizer scale]);
        CGAffineTransform transform = CGAffineTransformMakeScale(MINIMUM_SCALE,MINIMUM_SCALE);
        self.fullimageview.transform = transform;
    }
   else if ([recognizer scale]>MAXIMUM_SCALE) {
        NSLog(@"======== %f Scale Applied ===========",[recognizer scale]);
        CGAffineTransform transform = CGAffineTransformMakeScale(MAXIMUM_SCALE, MAXIMUM_SCALE);
        self.fullimageview.transform = transform;
   }else{
       NSLog(@"======== %f Scale Applied ===========",[recognizer scale]);
       CGAffineTransform transform = CGAffineTransformMakeScale([recognizer scale], [recognizer scale]);
       self.fullimageview.transform = transform;

   }
}
- (UIView *)viewForZoomingInScrollView:(UIScrollView *)scrollView
{
    return self.fullimageview;
}
- (void)scrollViewDidEndZooming:(UIScrollView *)scrollView withView:(UIView *)view atScale:(CGFloat)scale
{
    
}
-(void)animationDone:(UIView  *)view
{
    [self.scrlView removeFromSuperview];
    [self.viewbg removeFromSuperview];
    [self.fullimageview removeFromSuperview];
}
-(UIWindow *)keyWindow{
    return [UIApplication sharedApplication].keyWindow;
}
@end
