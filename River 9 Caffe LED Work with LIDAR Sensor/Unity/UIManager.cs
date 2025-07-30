using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class UIManager : MonoBehaviour
{
    public GameObject TemaMenuUI;
    public GameObject ZoomSliderUI;
    public GameObject MainMenuUI;

    CameraController cameraController;
    List<GameObject> menuList = new List<GameObject>();


    void Awake()
    {
        cameraController = Camera.main.GetComponent<CameraController>();
        DontDestroyOnLoad(gameObject);
    }

    void Start()
    {
        if (TemaMenuUI)
        {
            TemaMenuUI.GetComponent<TemaMenu>().InitializeTemaMenu();
            TemaMenuUI.SetActive(false);
            menuList.Add(TemaMenuUI);
        }
        if (ZoomSliderUI)
        {
            ZoomSliderUI.GetComponent<ZoomSlider>().InitializeZoomSlider();
            ZoomSliderUI.SetActive(false);
            menuList.Add(ZoomSliderUI);
        }
        if (MainMenuUI)
        {
            MainMenuUI.GetComponent<MainMenu>().InitializeMainMenu();
        }
        cameraController.OnMenuToggle += ToggleUIMenuList;
    }

    void ToggleUIMenuList()
    {
        foreach (GameObject objects in menuList)
        {
            if(objects.activeSelf)
            {
                objects.SetActive(false);
            }
            else
            {
                objects.SetActive(true);
            }
        }
    }
}
