//
//  ViewController.m
//  FullScreenProfilePic
//
//  Created by OWNER on 01/09/17.
//  Copyright © 2017 OWNER. All rights reserved.
//

#import "ViewController.h"
#import "UIImageView+Utils.h"

@interface ViewController (){
    IBOutlet UIImageView *temptumb,*fullview;
    
}

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.


    // PASS THE SUPER VIEW TO DISPLAY CONTENT
   [imageViewProfilePic methodPhotoViewerWithSuperView:self.view];
}
/*
- (void)bannerTapped:(UIGestureRecognizer *)gestureRecognizer {
    NSLog(@"%@", [gestureRecognizer view]);
    //create new image
    temptumb=(UIImageView *)gestureRecognizer.view;
    
    //fullview is gloabal, So we can acess any time to remove it
    fullview=[[UIImageView alloc]init];
    [fullview setContentMode:UIViewContentModeScaleAspectFit];
    [fullview setBackgroundColor:[UIColor colorWithPatternImage:[UIImage imageNamed:@"bckgrd.png"]]];
    fullview.image = [(UIImageView *)gestureRecognizer.view image];
    CGRect point=[self.view convertRect:gestureRecognizer.view.bounds fromView:gestureRecognizer.view];
    [fullview setFrame:point];
    
    [self.view addSubview:fullview];
    [UIView animateWithDuration:0.5
                     animations:^{
                         [fullview setFrame:CGRectMake(0,
                                                       0,
                                                       self.view.bounds.size.width,
                                                       self.view.bounds.size.height)];
                     }];
    UITapGestureRecognizer *singleTap = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(fullimagetapped:)];
    singleTap.numberOfTapsRequired = 1;
    singleTap.numberOfTouchesRequired = 1;
    [fullview addGestureRecognizer:singleTap];
    [fullview setUserInteractionEnabled:YES];
}

//This will remove the full screen and back to original location.

- (void)fullimagetapped:(UIGestureRecognizer *)gestureRecognizer {
    
    CGRect point=[self.view convertRect:temptumb.bounds fromView:temptumb];
    
    gestureRecognizer.view.backgroundColor=[UIColor clearColor];
    [UIView animateWithDuration:0.5
                     animations:^{
                         [(UIImageView *)gestureRecognizer.view setFrame:point];
                     }];
    [self performSelector:@selector(animationDone:) withObject:[gestureRecognizer view] afterDelay:0.4];
    
}

//Remove view after animation of remove
-(void)animationDone:(UIView  *)view
{
    //view.backgroundColor=[UIColor clearColor];
    [fullview removeFromSuperview];
    fullview=nil;
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

*/
@end
