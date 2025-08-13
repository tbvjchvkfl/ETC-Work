using UnityEngine;
using UnityEngine.UI;

public class ZoomSlider : MonoBehaviour
{
    public GameObject ZoomSlider_Obj;
    

    Slider zoomSlider;
    Camera MainCamera;

    float prevCameraPos = 0.0f;

    public void InitializeZoomSlider()
    {
        if (ZoomSlider_Obj)
        {
            zoomSlider = ZoomSlider_Obj.GetComponent<Slider>();
            zoomSlider.minValue = -20.0f;
            zoomSlider.maxValue = 20.0f;
            zoomSlider.value = 0.0f;
            zoomSlider.onValueChanged.AddListener(OnSliderValueChanged);
        }
        MainCamera = Camera.main;
    }

    void OnSliderValueChanged(float value)
    {
        if (MainCamera)
        {
            float delta = value - prevCameraPos;
            Vector3 forwardDirection = MainCamera.transform.forward * delta;
            Vector3 newPosition = MainCamera.transform.position + forwardDirection;
            MainCamera.transform.position = newPosition;
            prevCameraPos = value;
        }
    }
}
