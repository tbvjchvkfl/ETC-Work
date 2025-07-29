using UnityEngine;
using UnityEngine.SceneManagement;

public class UIManager : MonoBehaviour
{
    public GameObject TemaMenuUI;
    public GameObject ZoomSliderUI;

    CameraController cameraController;

    void Awake()
    {
        if (SceneManager.sceneCount == 0)
        {
            Debug.Log("main Menu");
        }
        else
        {
            cameraController = Camera.main.GetComponent<CameraController>();
        }
        DontDestroyOnLoad(gameObject);
    }

    void Start()
    {
        if (TemaMenuUI)
        {
            TemaMenuUI.GetComponent<TemaMenu>().InitializeTemaMenu();
        }
        if (ZoomSliderUI)
        {
            ZoomSliderUI.GetComponent<ZoomSlider>().InitializeZoomSlider();
        }

        cameraController.OnMenuToggle += ToggleUIMenuList;
    }

    void ToggleUIMenuList()
    {
        if (gameObject.activeSelf)
        {
            gameObject.SetActive(false);
        }
        else
        {
            gameObject.SetActive(true);
        }
    }
}
