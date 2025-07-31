using UnityEngine;
using UnityEngine.EventSystems;
using UnityEngine.SceneManagement;

public class MainMenu : MonoBehaviour
{
    public GameObject StartButton_Obj;
    public GameObject TemaSelectButton_Obj;
    public GameObject ExitButton_Obj;
    public GameObject TemaSelectMenu_Obj;
    public GameObject BackButton_Obj;

    MenuButton Start_Btn;
    MenuButton TemaSelect_Btn;
    MenuButton Exit_Btn;

    TemaChangeMenu temaChangeMenu;
    Animator animationController;

    int sceneIndex = 1;
    public bool bIsEnabledTemaSelect { get; set; } = false;

    public void InitializeMainMenu()
    {
        if (StartButton_Obj)
        {
            Start_Btn = StartButton_Obj.GetComponent<MenuButton>();
            Start_Btn.InitializeMenuButton();
            Start_Btn.OnStartButtonClicked += OnClickedStartButton;
        }
        if (TemaSelectButton_Obj)
        {
            TemaSelect_Btn = TemaSelectButton_Obj.GetComponent<MenuButton>();
            TemaSelect_Btn.InitializeMenuButton();
            TemaSelect_Btn.OnTemaSelectButtonClicked += OnClickedTemaSelectButton;
        }
        if (ExitButton_Obj)
        {
            Exit_Btn = ExitButton_Obj.GetComponent<MenuButton>();
            Exit_Btn.InitializeMenuButton();
        }
        if (TemaSelectMenu_Obj && BackButton_Obj)
        {
            temaChangeMenu = TemaSelectMenu_Obj.GetComponent<TemaChangeMenu>();
            temaChangeMenu.InitializedTemaChangeMenu(this.gameObject);
            temaChangeMenu.OnTemaChange += OnConfirmedSceneNumber;
            temaChangeMenu.OnTemaCancel += OnCancledChangeTema;
            TemaSelectMenu_Obj.SetActive(false);
            BackButton_Obj.SetActive(false);
        }
        animationController = GetComponent<Animator>();
        EventSystem.current.SetSelectedGameObject(StartButton_Obj);
    }

    void OnClickedStartButton()
    {
        SceneManager.LoadScene(sceneIndex);
    }

    void OnClickedTemaSelectButton()
    {
        animationController.SetBool("Clicked", true);
        TemaSelectMenu_Obj.SetActive(true);
        BackButton_Obj.SetActive(true);
        bIsEnabledTemaSelect = true;
    }

    void OnConfirmedSceneNumber(int sceneNum)
    {
        animationController.SetBool("Clicked", false);
        TemaSelectMenu_Obj.SetActive(false);
        BackButton_Obj.SetActive(false);
        sceneIndex = sceneNum;
        bIsEnabledTemaSelect = false;
        EventSystem.current.SetSelectedGameObject(TemaSelectMenu_Obj);
    }

    void OnCancledChangeTema()
    {
        bIsEnabledTemaSelect = false;
        animationController.SetBool("Clicked", false);
        TemaSelectMenu_Obj.SetActive(false);
        BackButton_Obj.SetActive(false);
        EventSystem.current.SetSelectedGameObject(TemaSelectMenu_Obj);
    }
}
