

struct CameraSettings
{
    double aspect_ratio = 16.0/9.0;
    double vertical_fov = 90.0;
    double aperture = 0; // determines how quickly stuff gets blurry away from focus_dist
    double focus_dist = 1; // distance at which objects are perfectly in focus.

    void depth_of_field(double aperture, double focus_dist)
    {
        // Created this function to avoid the case where you forget to change the aperture size
        // when setting focus distance.
        this->aperture = aperture;
        this->focus_dist = focus_dist;
    }
};