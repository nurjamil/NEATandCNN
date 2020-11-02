#include "cMain.h"

const int ID_TEXT = 10001;
const int ID_PANEL1 = 10002;
const int ID_PANEL2 = 10003;
const int ID_BUTTON_START = 10004;
const int ID_BUTTON2 = 10005;
const int ID_BUTTON_ADDLAYER = 10006;
const int ID_TEXT_FILTERTEXT = 10007;
const int ID_TEXT_OUTTEXT = 10008;
const int ID_COMBOBOX1 = 10009;
const int ID_BUTTON_LOADTEST = 10010;
const int ID_BUTTON_TEST = 10011;
const int ID_BUTTON_LOADTESTDATA1CLASS = 10012;
const int ID_BUTTON_LOADFILE = 10013;
const int ID_BUTTON_SAVEFILE = 10014;
const int ID_TEXT_CLASS = 10015;
const int ID_BUTTON_LOADTRAINDATA = 10016;
const int ID_BUTTON_CLEARTRAINDATA = 10017;
const int ID_BUTTON_CLEARTESTDATA = 10018;
const int ID_BUTTON_SETLEARNINGRATE = 10019;
const int ID_TEXT_LEARNINGRATE = 10020;
const int ID_BUTTON_TESTNEAT = 10021;
const int ID_BUTTON_TRAINNEAT = 10022;
const int ID_BUTTON_LOADTRAINNEAT = 10023;
const int ID_BUTTON_LOADTESTNEAT = 10024;
const int ID_BUTTON_LOADVALIDNEAT = 10025;
const int ID_BUTTON_LOADTEST1CLASSNEAT = 10026;
const int ID_BUTTON_SETLEARNINGRATENEAT = 10027;
const int ID_BUTTON_SETSTRUCTURENEAT = 10028;
const int ID_TEXT_1CLASSNEAT = 10029;
const int ID_TEXT_SETLEARNINGRATENEAT = 10030;
const int ID_TEXT_NUMINPUTNEAT = 10031;
const int ID_TEXT_NUMHIDDENNEAT = 10032;
const int ID_TEXT_NUMPOPULATIONNEAT = 10033;
const int ID_TEXT_NUMOUTPUTNEAT = 10034;
const int ID_TEXT_OUTPUTNEAT = 10035;
const int ID_BUTTON_LOADNEAT = 10036;
const int ID_BUTTON_SAVENEAT = 10037;
const int ID_BUTTON_CLEARTESTDATANEAT = 10038;
const int ID_BUTTON_RESETLAYER = 10039;
const int ID_BUTTON_RESETSTRUCTURE = 10040;
const int ID_BUTTON_PREDICT_CNN = 10041;
const int ID_BUTTON_PREDICT_NEAT = 10042;
cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Klasifikasi gambar", wxPoint(30, 30), wxSize(800, 600))
{
	wxNotebook *note = new wxNotebook(this, -1, wxPoint(-1, -1),
		wxSize(-1, -1), wxNB_TOP);
	//CNN PANEL
	wxBoxSizer *verticalSizer = new wxBoxSizer(wxVERTICAL);
	panel = new wxPanel(note, -1);
	panel->SetBackgroundColour(wxColour(*wxGREEN));

	//button stat/test/setdata
	btnStart = new wxButton(panel, ID_BUTTON_START, "TRAIN", wxDefaultPosition);
	TestData = new wxButton(panel, ID_BUTTON_LOADTEST, "LOAD TEST DATA", wxDefaultPosition);
	btnTest = new wxButton(panel, ID_BUTTON_TEST, "TEST", wxDefaultPosition);
	loadTrainData = new wxButton(panel, ID_BUTTON_LOADTRAINDATA, "LOAD TRAIN DATA");
	//loadTestData1class = new wxButton(panel, ID_BUTTON_LOADTESTDATA1CLASS, "LOAD TEST DATA(1 KELAS)", wxDefaultPosition);
	//wxStaticText *staticText1Class = new wxStaticText(panel, -1, "Kelas Index : ", wxDefaultPosition, wxSize(30, 30));
	//sText1Class = new wxTextCtrl(panel, ID_TEXT_CLASS, "", wxDefaultPosition, wxSize(30, 30));
	wxBoxSizer *StartSizer = new wxBoxSizer(wxHORIZONTAL);
	StartSizer->Add(btnStart, 1, wxALL, 2);
	StartSizer->Add(btnTest, 1, wxALL, 2);
	StartSizer->Add(loadTrainData, 1, wxALL, 2);
	StartSizer->Add(TestData, 1, wxALL, 2);
	//StartSizer->Add(loadTestData1class, 1, wxALL, 2);
	//StartSizer->Add(staticText1Class, 0, wxALL, 2);
	//StartSizer->Add(sText1Class, 0, wxALL, 2);
	verticalSizer->Add(StartSizer,0,wxALL,5);


	//buttonClearTrainData = new wxButton(panel, ID_BUTTON_CLEARTRAINDATA, "Clear Train Data");
	//buttonClearTestData = new wxButton(panel, ID_BUTTON_CLEARTESTDATA, "clear test data");
	loadFile = new wxButton(panel, ID_BUTTON_LOADFILE, "LOAD FILE");
	saveFile = new wxButton(panel, ID_BUTTON_SAVEFILE, "SAVE FILE");
	//resetLayer = new wxButton(panel, ID_BUTTON_RESETLAYER, "reset CNN layer");
	//predict = new wxButton(panel, ID_BUTTON_PREDICT_CNN, "Predict", wxDefaultPosition);
	wxBoxSizer *secondSizer = new wxBoxSizer(wxHORIZONTAL);
	//secondSizer->Add(predict, 1, wxALL, 2);
	//secondSizer->Add(buttonClearTrainData, 1, wxALL, 2);
	//secondSizer->Add(buttonClearTestData, 1, wxALL, 2);
	secondSizer->Add(loadFile, 1, wxALL, 2);
	secondSizer->Add(saveFile, 1, wxALL, 2);
	//secondSizer->Add(resetLayer, 1, wxALL, 2);
	verticalSizer->Add(secondSizer,0, wxALL ,5);


	//combobox
	wxString str[] = { "maxpool","convolution2d","flatten","fullyConnected","output" };
	sizer3 = new wxBoxSizer(wxHORIZONTAL);
	//combo = new wxComboBox(panel, ID_COMBOBOX1, wxT("pilih layer"), wxDefaultPosition, wxDefaultSize, 5, str);
	//buttonAddLayer = new wxButton(panel, ID_BUTTON_ADDLAYER, wxT("Add Layer"), wxDefaultPosition);
	//sTextFilterSize = new wxStaticText(panel, wxID_ANY, "filterSize : ");
	//sTextOut = new wxStaticText(panel, wxID_ANY, "out : ");
	//filterSizeText = new wxTextCtrl(panel, ID_TEXT_FILTERTEXT, "", wxDefaultPosition, wxSize(25, 25));
	//out = new wxTextCtrl(panel, ID_TEXT_OUTTEXT, "", wxDefaultPosition, wxSize(25, 25));
	///buttonSetLearningRate = new wxButton(panel, ID_BUTTON_SETLEARNINGRATE, "set learning rate :");
	//textLearningRate = new wxTextCtrl(panel, ID_TEXT_LEARNINGRATE, "", wxDefaultPosition, wxSize(50, 25));
	sizer3->Add(combo, 1, wxALL, 2);
	sizer3->Add(sTextFilterSize, 0, wxALL, 2);
	sizer3->Add(filterSizeText, 0, wxALL, 2);
	sizer3->Add(sTextOut, 0, wxALL, 2);
	sizer3->Add(out, 0, wxALL, 2);
	sizer3->Add(buttonAddLayer, 1, wxALL, 2);
	sizer3->Add(buttonSetLearningRate, 1, wxALL, 2);
	sizer3->Add(textLearningRate, 0, wxALL, 2);
	//verticalSizer->Add(sizer3, 0,wxALL,5);
	sizer3->Hide(1);
	sizer3->Hide(2);
	sizer3->Hide(3);
	sizer3->Hide(4);


	//output
	text = new wxTextCtrl(panel, ID_TEXT, "", wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
	wxBoxSizer *TextSizer = new wxBoxSizer(wxHORIZONTAL);
	TextSizer->Add(text, 1, wxEXPAND | wxALL, 2);
	verticalSizer->Add(TextSizer,1, wxEXPAND | wxALL, 5);

	panel->SetSizer(verticalSizer);




	Connect(ID_TEXT, wxEVT_TEXT, wxCommandEventHandler(cMain::TextEntered));
	Connect(ID_COMBOBOX1, wxEVT_COMBOBOX, wxCommandEventHandler(cMain::ComboSelected));
	Connect(ID_BUTTON_START, wxEVT_BUTTON, wxCommandEventHandler(cMain::ButtonStartClicked));
	Connect(ID_BUTTON_LOADTEST, wxEVT_BUTTON, wxCommandEventHandler(cMain::ButtonLoadTestDataClicked));
	Connect(ID_BUTTON_LOADTESTDATA1CLASS, wxEVT_BUTTON, wxCommandEventHandler(cMain::ButtonLoadTestData1ClassClicked));
	Connect(ID_BUTTON_TEST, wxEVT_BUTTON, wxCommandEventHandler(cMain::ButtonTestClicked));
	Connect(ID_BUTTON_ADDLAYER, wxEVT_BUTTON, wxCommandEventHandler(cMain::ButtonAddLayerClicked));
	Connect(ID_BUTTON_LOADTRAINDATA, wxEVT_BUTTON, wxCommandEventHandler(cMain::ButtonLoadTrainDataClicked));
	Connect(ID_BUTTON_CLEARTRAINDATA, wxEVT_BUTTON, wxCommandEventHandler(cMain::ButtonClearTrainDataClicked));
	Connect(ID_BUTTON_CLEARTESTDATA, wxEVT_BUTTON, wxCommandEventHandler(cMain::ButtonClearTestDataClicked));
	Connect(ID_BUTTON_SETLEARNINGRATE, wxEVT_BUTTON, wxCommandEventHandler(cMain::ButtonSetLearningRateClicked));
	Connect(ID_BUTTON_SAVEFILE, wxEVT_BUTTON, wxCommandEventHandler(cMain::ButtonSaveClicked));
	Connect(ID_BUTTON_LOADFILE, wxEVT_BUTTON, wxCommandEventHandler(cMain::ButtonLoadClicked));
	Connect(ID_BUTTON_RESETLAYER,wxEVT_BUTTON, wxCommandEventHandler(cMain::buttonResetLayer));
	Connect(ID_BUTTON_PREDICT_CNN, wxEVT_BUTTON, wxCommandEventHandler(cMain::buttonPredict));

	//NEATPANEL
	wxPanel *panel2 = new wxPanel(note, -1);
	panel2->SetBackgroundColour(wxColour(*wxGREEN));
	wxBoxSizer *verticalNEATSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *sizerNEAT1 = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *sizerNEAT2 = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *sizerNEAT3 = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *sizerNEAT4 = new wxBoxSizer(wxHORIZONTAL);
	buttonTrainNEAT = new wxButton(panel2, ID_BUTTON_TRAINNEAT, "TRAIN");
	buttonTestNEAT = new wxButton(panel2, ID_BUTTON_TESTNEAT, "TEST");
	buttonLoadTrainDataNEAT = new wxButton(panel2, ID_BUTTON_LOADTRAINNEAT, "Load Train Data");
	buttonLoadValidationDataNEAT = new wxButton(panel2, ID_BUTTON_LOADVALIDNEAT, "Load Validation Data");
	buttonLoadTestDataNEAT = new wxButton(panel2, ID_BUTTON_LOADTESTNEAT, "Load Test Data");
	//butonLoadTest1ClassDataNEAT = new wxButton(panel2, ID_BUTTON_LOADTEST1CLASSNEAT, "Load Test data untuk kelas :");
	//sText1ClassNEAT = new wxStaticText(panel2, -1, "index : ");
	//text1ClassNEAT = new wxTextCtrl(panel2, ID_TEXT_1CLASSNEAT, "");
	//buttonClearTestDataNEAT = new wxButton(panel2, ID_BUTTON_CLEARTESTDATANEAT, "Clear test data");
	buttonLoadNEAT = new wxButton(panel2, ID_BUTTON_LOADNEAT, "Load");
	buttonSaveNEAT = new wxButton(panel2, ID_BUTTON_SAVENEAT, "Save");
	//buttonResetStructure = new wxButton(panel2, ID_BUTTON_RESETSTRUCTURE, "Reset struktur");
	//buttonSetLearningRateNEAT = new wxButton(panel2, ID_BUTTON_SETLEARNINGRATENEAT, "Set Learning Rate :");
	//textSetLearningRateNEAT = new wxTextCtrl(panel2, ID_TEXT_SETLEARNINGRATENEAT, "", wxDefaultPosition, wxSize(35, 25));
	//buttonSetStructureNEAT = new wxButton(panel2, ID_BUTTON_SETSTRUCTURENEAT, "Set Struktur");
	///sTextNumInputNEAT = new wxStaticText(panel2, -1, "Jumlah Input : ");
	//textNumInputNEAT = new wxTextCtrl(panel2, ID_TEXT_NUMINPUTNEAT, "", wxDefaultPosition, wxSize(35, 25));
	//sTextNumHiddenNEAT = new wxStaticText(panel2, -1, "Jumlah hidden : ");
	//textNumHiddenNEAT = new wxTextCtrl(panel2, ID_TEXT_NUMHIDDENNEAT, "", wxDefaultPosition, wxSize(35, 25));
	//sTextNumOutputNEAT = new wxStaticText(panel2, -1, "Jumlah output : ");
	//textNumOutputNEAT = new wxTextCtrl(panel2, ID_TEXT_NUMOUTPUTNEAT, "", wxDefaultPosition, wxSize(35, 25));
	//sTextNumPopulationNEAT = new wxStaticText(panel2, -1, "Jumlah populasi : ");
	//textNumPopulationNEAT = new wxTextCtrl(panel2, ID_TEXT_NUMPOPULATIONNEAT, "", wxDefaultPosition, wxSize(35, 25));
	outputNEAT = new wxTextCtrl(panel2, ID_TEXT_OUTPUTNEAT,"",wxDefaultPosition,wxDefaultSize,wxTE_MULTILINE);
	//predictNEAT = new wxButton(panel2, ID_BUTTON_PREDICT_NEAT, "Predict", wxDefaultPosition);


	sizerNEAT1->Add(buttonLoadNEAT, 1, wxALL, 2);
	sizerNEAT1->Add(buttonSaveNEAT, 1, wxALL, 2);
	sizerNEAT1->Add(buttonTrainNEAT, 1, wxALL, 2);
	sizerNEAT1->Add(buttonTestNEAT, 1, wxALL, 2);
	sizerNEAT1->Add(predictNEAT, 1, wxALL, 2);
	sizerNEAT1->Add(buttonLoadTrainDataNEAT, 1, wxALL, 2);
	sizerNEAT1->Add(buttonLoadValidationDataNEAT, 1, wxALL, 2);
	sizerNEAT2->Add(buttonLoadTestDataNEAT, 1, wxALL, 2);
	//sizerNEAT2->Add(butonLoadTest1ClassDataNEAT, 1, wxALL, 2);
	//sizerNEAT2->Add(sText1ClassNEAT, 0, wxALL, 2);
	//sizerNEAT2->Add(text1ClassNEAT, 0, wxALL, 2);
	//sizerNEAT2->Add(buttonClearTestDataNEAT, 1, wxALL, 2);
	//sizerNEAT2->Add(buttonResetStructure, 1, wxALL, 2);
	//sizerNEAT3->Add(buttonSetLearningRateNEAT, 1, wxALL, 2);
	//sizerNEAT3->Add(textSetLearningRateNEAT, 1, wxALL, 2);
	//sizerNEAT3->Add(buttonSetStructureNEAT, 1, wxALL, 2);
	//sizerNEAT3->Add(sTextNumInputNEAT, 0, wxALL, 2);
	//sizerNEAT3->Add(textNumInputNEAT, 0, wxALL, 2);
	//sizerNEAT3->Add(sTextNumHiddenNEAT, 0, wxALL, 2);
	//sizerNEAT3->Add(textNumHiddenNEAT, 0, wxALL, 2);
	//sizerNEAT3->Add(sTextNumOutputNEAT, 0, wxALL, 2);
	//sizerNEAT3->Add(textNumOutputNEAT, 0, wxALL, 2);
	//sizerNEAT3->Add(sTextNumPopulationNEAT, 0, wxALL, 2);
	//sizerNEAT3->Add(textNumPopulationNEAT, 0, wxALL, 2);
	sizerNEAT4->Add(outputNEAT, 1, wxEXPAND | wxALL, 5);
	verticalNEATSizer->Add(sizerNEAT1,0,wxALL,5);
	verticalNEATSizer->Add(sizerNEAT2, 0, wxALL, 5);
	verticalNEATSizer->Add(sizerNEAT3, 0, wxALL, 5);
	verticalNEATSizer->Add(sizerNEAT4, 1, wxEXPAND | wxALL, 5);
	panel2->SetSizer(verticalNEATSizer,wxALIGN_LEFT);


	Connect(ID_BUTTON_SAVENEAT, wxEVT_BUTTON, wxCommandEventHandler(cMain::buttonSaveClickedNEAT));
	Connect(ID_BUTTON_LOADNEAT, wxEVT_BUTTON, wxCommandEventHandler(cMain::buttonLoadClickedNEAT));
	Connect(ID_BUTTON_LOADTRAINNEAT, wxEVT_BUTTON, wxCommandEventHandler(cMain::buttonLoadTrainDataClickedNEAT));
	Connect(ID_BUTTON_LOADVALIDNEAT, wxEVT_BUTTON, wxCommandEventHandler(cMain::buttonLoadValidationDataClickedNEAT));
	Connect(ID_BUTTON_LOADTESTNEAT, wxEVT_BUTTON, wxCommandEventHandler(cMain::buttonLoadTestDataClickedNEAT));
	Connect(ID_BUTTON_LOADTEST1CLASSNEAT, wxEVT_BUTTON, wxCommandEventHandler(cMain::buttonLoadTest1ClassDataClickedNEAT));
	Connect(ID_BUTTON_TRAINNEAT, wxEVT_BUTTON, wxCommandEventHandler(cMain::buttonTrainClickedNEAT));
	Connect(ID_BUTTON_TESTNEAT, wxEVT_BUTTON, wxCommandEventHandler(cMain::buttonTestClickedNEAT));
	Connect(ID_BUTTON_SETLEARNINGRATENEAT, wxEVT_BUTTON, wxCommandEventHandler(cMain::buttonSetLearningRateClickedNEAT));
	Connect(ID_BUTTON_SETSTRUCTURENEAT, wxEVT_BUTTON, wxCommandEventHandler(cMain::buttonSetStructureClickedNEAT));
	Connect(ID_TEXT_OUTPUTNEAT, wxEVT_BUTTON, wxCommandEventHandler(cMain::buttonTextOutputNEAT));
	Connect(ID_BUTTON_CLEARTESTDATANEAT, wxEVT_BUTTON, wxCommandEventHandler(cMain::buttonClearTestDataNEATClicked));
	Connect(ID_BUTTON_RESETSTRUCTURE, wxEVT_BUTTON, wxCommandEventHandler(cMain::buttonResetStructureClicked));
	Connect(ID_BUTTON_PREDICT_NEAT, wxEVT_BUTTON, wxCommandEventHandler(cMain::buttonPredictNEAT));

	note->AddPage(panel, wxT("CNN"));
	note->AddPage(panel2, wxT("NEAT"));

	//initialize CNN
	CNN = new convolution_layer(0.0005, 0.99, false);
	CNN->addLayer1(5,16, Layer_type::convoluteRelu);
	CNN->addLayer3(Layer_type::maxPool);
	CNN->addLayer1(3,32, Layer_type::convoluteRelu);
	CNN->addLayer3(Layer_type::maxPool);
	CNN->addLayer3(Layer_type::flatten);
	CNN->addLayer2(128, Layer_type::fullyConn);
	CNN->addLayer2(8, Layer_type::fullyConnSoftmax);

	//initialize NEAT
	neat = new NEAT(784, 20, 8, 20);

	
}


cMain::~cMain()
{
}

void cMain::TextEntered(wxCommandEvent &event) {
	int pos = text->GetLastPosition();
	text->ShowPosition(pos);
}

void cMain::ButtonStartClicked(wxCommandEvent &event) {
	if (in.data.size() <= 0) {
		wxMessageDialog *dial = new wxMessageDialog(NULL,
			wxT("Masukkan data latih terlebih dahulu!"), wxT("Info"), wxOK);
		dial->ShowModal();
		return;
	}
	if (btnStart->GetLabel() == wxT("TRAIN") && isLanjut == false) {
		btnStart->SetLabel(wxT("STOP"));
		isLanjut = true;
		m_pThread = new MyThread(this, CNN,type::training);
		m_pThread->Create();
		m_pThread->Run();
		
	}
	else if (btnStart->GetLabel() == wxT("TRAIN") && isLanjut == true) {
		wxMessageDialog *dial = new wxMessageDialog(NULL,
			wxT("tidak dapat memulai training!"), wxT("Info"), wxOK);
		dial->ShowModal();
	}
	else {
		btnStart->SetLabel(wxT("TRAIN"));
		isLanjut = false;
	}
	
	event.Skip();
}
void cMain::ButtonLoadTestData1ClassClicked(wxCommandEvent &event) {
	if (sText1Class->GetValue() == "") {
		wxMessageDialog *dial = new wxMessageDialog(NULL,
			wxT("set index kelas terlebih dahulu!"), wxT("Info"), wxOK);
		dial->ShowModal();
		return;
	}
	wxDirDialog dlg(NULL, "Choose input directory", "",
		wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);
	if (dlg.ShowModal() == wxID_CANCEL)
		return;
	in2.readFolder(std::string(dlg.GetPath().mb_str(wxConvUTF8)),wxAtoi(sText1Class->GetValue()));
}

void cMain::ButtonTestClicked(wxCommandEvent &event) {
	if (in2.data.size() <= 0) {
		wxMessageDialog *dial = new wxMessageDialog(NULL,
			wxT("Masukkan data test terlebih dahulu!"), wxT("Info"), wxOK);
		dial->ShowModal();
		return;
	}
	if (isLanjut == false) {
		m_pThread = new MyThread(this, CNN, type::testing);
		m_pThread->Create();
		m_pThread->Run();
	}
	else {
		wxMessageDialog *dial = new wxMessageDialog(NULL,
			wxT("selesaikan training terlebih dahulu!"), wxT("Info"), wxOK);
		dial->ShowModal();
	}
}
void cMain::ButtonLoadTrainDataClicked(wxCommandEvent &event) {
	
	wxDirDialog dlg(NULL, "Choose input directory", "",
		wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);
	if (dlg.ShowModal() == wxID_CANCEL)
		return;
	in.LoadFromOneFolder(std::string(dlg.GetPath().mb_str(wxConvUTF8)));
	wxMessageDialog *dial = new wxMessageDialog(NULL,
		wxT("loading completed"), wxT("Info"), wxOK);
	dial->ShowModal();
}

void cMain::load() {
	

}


void cMain::ButtonLoadTestDataClicked(wxCommandEvent &event) {
	wxDirDialog dlg(NULL, "Choose input directory", "",
		wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);
	if (dlg.ShowModal() == wxID_CANCEL)
		return;
	in2.LoadFromOneFolder(std::string(dlg.GetPath().mb_str(wxConvUTF8)));

}

void cMain::ButtonLoadClicked(wxCommandEvent &event) {
	wxFileDialog
		openFileDialog(this, _("Open CNN FILE"), "", "",
			"*.txt", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (openFileDialog.ShowModal() == wxID_CANCEL)
		return;
	std::string str = std::string(openFileDialog.GetPath().mb_str(wxConvUTF8));
	delete CNN;
	CNN = nullptr;
	CNN = new convolution_layer;
	std::ifstream masuk(str);
	masuk >> *CNN;
	masuk.close();
}

void cMain::ButtonSaveClicked(wxCommandEvent &event) {
	wxFileDialog
		saveFileDialog(this, _("Save CNN file"), "", "",
			"*.txt", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
	if (saveFileDialog.ShowModal() == wxID_CANCEL)
		return;     // the user changed idea...
	std::string str = std::string(saveFileDialog.GetPath().mb_str(wxConvUTF8));
	std::ofstream save123(str);

	// Write objects to file
	save123 << *CNN;

	save123.close();
}
void cMain::ButtonAddLayerClicked(wxCommandEvent &event) {
	if (combo->GetCurrentSelection() == 0) {
		CNN->getIsInitialized() = false;
		CNN->addLayer3(Layer_type::maxPool);
		wxMessageDialog *dial = new wxMessageDialog(NULL,
			wxT("Tambah Layer : Maxpool"), wxT("Info"), wxOK);
		dial->ShowModal();
	}
	else if (combo->GetCurrentSelection() == 1) {
		CNN->getIsInitialized() = false;
		CNN->addLayer1(wxAtoi(filterSizeText->GetValue()), wxAtoi(out->GetValue()), Layer_type::convoluteRelu);
		wxString str = "tambah layer convolution!!! \n filter : " + filterSizeText->GetValue() + "feature map :" +  out->GetValue();
		wxMessageDialog *dial = new wxMessageDialog(NULL,
			str, wxT("Info"), wxOK);
		dial->ShowModal();
	}
	else if (combo->GetCurrentSelection() == 2) {
		CNN->getIsInitialized() = false;
		CNN->addLayer3(Layer_type::flatten);
		wxMessageDialog *dial = new wxMessageDialog(NULL,
			wxT("Tambah Layer : flatten"), wxT("Info"), wxOK);
		dial->ShowModal();
	}
	else if (combo->GetCurrentSelection() == 3) {
		CNN->getIsInitialized() = false;
		CNN->addLayer2(wxAtoi(out->GetValue()), Layer_type::fullyConn);
		wxString str = "tambah layer fullyConnected!!, output : " +  out->GetValue();
		wxMessageDialog *dial = new wxMessageDialog(NULL,
			str, wxT("Info"), wxOK);
		dial->ShowModal();
	}
	else if (combo->GetCurrentSelection() == 4) {
		CNN->getIsInitialized() = false;
		CNN->addLayer2(wxAtoi(out->GetValue()), Layer_type::fullyConnSoftmax);
		wxString str = "tambah layer output!!, output : " + out->GetValue();
		wxMessageDialog *dial = new wxMessageDialog(NULL,
			str, wxT("Info"), wxOK);
		dial->ShowModal();
	}
}

void* MyThread::Entry()
{
	convolution_layer *CNNTemp = new convolution_layer;
	if (tipe == type::training) {
		isRunning = true;
		
		while (isLanjut)
		{
			// ... do a bit of work...
			*m_pHandler->text << "Training..." << "\n";
			*CNNTemp = *CNN;
			++epoch;
			auto rng = std::default_random_engine{};
			std::shuffle(std::begin(m_pHandler->getInputTrain().data), std::end(m_pHandler->getInputTrain().data), rng);
			double akurasi = m_pHandler->CNN->training(m_pHandler->getInputTrainConst().data, 1,isLanjut);
			if (akurasi >= 0.0) {
				*m_pHandler->text << "JUMLAH DATA = " << std::to_string(m_pHandler->getInputTrain().data.size()) << "\n";
				*m_pHandler->text << "epoch " << epoch << " : \n";
				*m_pHandler->text << "akurasi training : " << std::to_string(akurasi) << "\n";
				*CNNTemp = *CNN;
			}
			else {
				*CNN = *CNNTemp;
			}

		}
		isRunning = false;
		delete CNNTemp;
		wxMessageDialog *dial = new wxMessageDialog(NULL,
			wxT("selesai training!"), wxT("Info"), wxOK);
		dial->ShowModal();
		*m_pHandler->text << "Training telah berhenti!" << "\n";
	}
	else if (tipe == type::testing) {
		*m_pHandler->text << "Testing..." << "\n";
		isLanjut = true;
		double akurasi = m_pHandler->CNN->test(m_pHandler->getInputTest().data);
		*m_pHandler->text << "JUMLAH DATA = " << std::to_string(m_pHandler->getInputTest().data.size()) << "\n";
		*m_pHandler->text <<"akurasi testing : "<< std::to_string(akurasi) << "\n";
		wxMessageDialog *dial = new wxMessageDialog(NULL,
			wxT("selesai testing!"), wxT("Info"), wxOK);
		isLanjut = false;
	}
	// signal the event handler that this thread is going to be destroyed
	// NOTE: here we assume that using the m_pHandler pointer is safe,
	//       (in this case this is assured by the MyFrame destructor)
	return 0;
	// success
}

void* ThreadNEAT::Entry() {
	if (tipe == type::training) {
		NEAT *tempNEAT = new NEAT;
		while (isLanjutNEAT) {
			NEAT *tempNEAT2 = new NEAT;
			*tempNEAT2 = *m_pHandler->neat;
			tempNEAT2->copyPop(*m_pHandler->neat);
			++generation;
			int count = 0;
			auto rng = std::default_random_engine{};
			std::shuffle(std::begin(m_pHandler->neat->training.data), std::end(m_pHandler->neat->training.data), rng);
			*m_pHandler->outputNEAT << "population size" << std::to_string(m_pHandler->neat->population.size()) << "\n";
			for (auto &ind : m_pHandler->neat->population) {
				*m_pHandler->outputNEAT << "individu " << std::to_string(count++) << "gen size" << std::to_string(ind->gen.size()) << "\n";
				*m_pHandler->outputNEAT << "Akurasi training : " << std::to_string(ind->calculate_fitness(m_pHandler->neat->training.data, isLanjutNEAT)) << " ";
				*m_pHandler->outputNEAT << "Akurasi validation : " << std::to_string(ind->classPredicted(m_pHandler->neat->validation.data, isLanjutNEAT)) << "\n";
				if (!isLanjutNEAT) {
					if (tempNEAT->population.size() > 0) {
						NEAT *temp = m_pHandler->neat;
						m_pHandler->neat = tempNEAT;
						tempNEAT = nullptr;
						delete temp;
					}
					else {
						NEAT *temp = m_pHandler->neat;
						m_pHandler->neat = tempNEAT2;
						tempNEAT2 = nullptr;
						delete temp;
					}
					wxMessageDialog *dial = new wxMessageDialog(NULL,
						wxT("selesai training!"), wxT("Info"), wxOK);
					dial->ShowModal();
					return 0;
				}
			}
			*tempNEAT = *m_pHandler->neat;
			tempNEAT->copyPop(*m_pHandler->neat);
			//std::cout << "species size : " << list_species.size() << std::endl;
			m_pHandler->neat->speciation();
			//*m_pHandler->outputNEAT << "species size : " << std::to_string(m_pHandler->neat->list_species.size()) << "\n";
			m_pHandler->neat->crossover();
			m_pHandler->neat->mutation();
			if (tempNEAT2 != nullptr)
				delete tempNEAT2;
		}
	}
	else if(tipe == type::testing){
		isLanjutNEAT = true;
		size_t index = 0;
		double fitness = 0.0;
		for (size_t i = 0; i < m_pHandler->neat->population.size(); ++i) {
			if (m_pHandler->neat->population[i]->getFitness() > fitness) {
			index = i;
			fitness = m_pHandler->neat->population[i]->getFitness();
			}
		}
		*m_pHandler->outputNEAT << "Akurasi testing : " << std::to_string(m_pHandler->neat->population[index]->classPredicted(m_pHandler->test.data, isLanjutNEAT)) << "\n";
		m_pHandler->neat->population[index]->fitness = fitness;
		isLanjutNEAT = false;
	}
	return 0;
}

void cMain::ComboSelected(wxCommandEvent &event) {
	if (combo->GetValue() == wxT("convolution2d")) {
		sizer3->Show((size_t)1);
		sizer3->Show(2,true);
		sizer3->Show(3,true);
		sizer3->Show(4,true);
		panel->Layout();

	}
	else if (combo->GetValue() == wxT("fullyConnected") || combo->GetValue() == wxT("output")) {
		sizer3->Hide(1);
		sizer3->Hide(2);
		sizer3->Show(3, true);
		sizer3->Show(4, true);
		panel->Layout();
	}
	else {
		sizer3->Hide(1);
		sizer3->Hide(2);
		sizer3->Hide(3);
		sizer3->Hide(4);
		panel->Layout();
	}
}

void cMain::ButtonClearTrainDataClicked(wxCommandEvent &event) {
	in.data.clear();
	in.data.shrink_to_fit();
	wxMessageDialog *dial = new wxMessageDialog(NULL,
		wxT("sukses menghapus data training!"), wxT("Info"), wxOK);
	dial->ShowModal();
}
void cMain::ButtonClearTestDataClicked(wxCommandEvent &event) {
	in2.data.clear();
	in2.data.shrink_to_fit();
	wxMessageDialog *dial = new wxMessageDialog(NULL,
		wxT("sukses menghapus data testing!"), wxT("Info"), wxOK);
	dial->ShowModal();
}

void cMain::ButtonSetLearningRateClicked(wxCommandEvent &event) {
	double value;
	textLearningRate->GetValue().ToDouble(&value);
	CNN->learning_rate = value;
}
void cMain::buttonTextOutputNEAT(wxCommandEvent &event) {
	int pos = outputNEAT->GetLastPosition();
	outputNEAT->ShowPosition(pos);
}
void cMain::buttonLoadClickedNEAT(wxCommandEvent &event) {
	wxFileDialog
		openFileDialog(this, _("Open NEAT FILE"), "", "",
			"*.txt", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (openFileDialog.ShowModal() == wxID_CANCEL)
		return;
	std::string str = std::string(openFileDialog.GetPath().mb_str(wxConvUTF8));
	if(neat != nullptr)
	delete neat;
	neat = nullptr;
	neat = new NEAT;
	std::ifstream masuk(str);
	masuk >> *neat;
	masuk.close();
}
void cMain::buttonTestClickedNEAT(wxCommandEvent &event) {
if (test.data.size() <= 0) {
	wxMessageDialog *dial = new wxMessageDialog(NULL,
		wxT("Masukkan data test terlebih dahulu!"), wxT("Info"), wxOK);
	dial->ShowModal();
	return;
}
	if (neat == nullptr) {
		wxMessageDialog *dial = new wxMessageDialog(NULL,
			wxT("buat structure terlebih dahulu!"), wxT("Info"), wxOK);
		dial->ShowModal();
		return;
	}
	if (isLanjutNEAT == false) {
		thd_NEAT = new ThreadNEAT(this, type::testing);
		thd_NEAT->Create();
		thd_NEAT->Run();
	}
	else {
		wxMessageDialog *dial = new wxMessageDialog(NULL,
			wxT("tidak dapat memulai testing!"), wxT("Info"), wxOK);
		dial->ShowModal();
	}
}
void cMain::buttonSaveClickedNEAT(wxCommandEvent &event) {
	if (neat == nullptr) {
		wxMessageDialog *dial = new wxMessageDialog(NULL,
			wxT("error!"), wxT("Info"), wxOK);
		dial->ShowModal();
		return;
	}
	wxFileDialog
		saveFileDialog(this, _("Save NEAT file"), "", "",
			"*.txt", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
	if (saveFileDialog.ShowModal() == wxID_CANCEL)
		return;     // the user changed idea...
	std::string str = std::string(saveFileDialog.GetPath().mb_str(wxConvUTF8));
	std::ofstream save123(str);

	// Write objects to file
	save123 << *neat;

	save123.close();
}
void cMain::buttonTrainClickedNEAT(wxCommandEvent &event) {
	if (neat->getTraining().data.size() <= 0 || neat->getValidation().data.size()<=0) {
		wxMessageDialog *dial = new wxMessageDialog(NULL,
			wxT("Masukkan data latih terlebih dahulu!"), wxT("Info"), wxOK);
		dial->ShowModal();
		return;
	}
	if (neat == nullptr) {
		wxMessageDialog *dial = new wxMessageDialog(NULL,
			wxT("buat structure terlebih dahulu!"), wxT("Info"), wxOK);
		dial->ShowModal();
		return;
	}
	if (buttonTrainNEAT->GetLabel() == wxT("TRAIN") && isLanjutNEAT == false) {
		buttonTrainNEAT->SetLabel(wxT("STOP"));
		isLanjutNEAT = true;
		thd_NEAT = new ThreadNEAT(this, type::training);
		thd_NEAT->Create();
		thd_NEAT->Run();

	}
	else if (buttonTrainNEAT->GetLabel() == wxT("TRAIN") && isLanjutNEAT == true) {
		wxMessageDialog *dial = new wxMessageDialog(NULL,
			wxT("tidak dapat memulai training!"), wxT("Info"), wxOK);
		dial->ShowModal();
	}
	else {
		buttonTrainNEAT->SetLabel(wxT("TRAIN"));
		isLanjutNEAT = false;
	}
}
void cMain::buttonLoadTrainDataClickedNEAT(wxCommandEvent &event) {
	if (neat == nullptr) {
		wxMessageDialog *dial = new wxMessageDialog(NULL,
			wxT("buat structure terlebih dahulu!"), wxT("Info"), wxOK);
		dial->ShowModal();
		return;
	}
	wxDirDialog dlg(NULL, "Choose input directory", "",
		wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);
	if (dlg.ShowModal() == wxID_CANCEL)
		return;
	//train.LoadFromOneFolder(std::string(dlg.GetPath().mb_str(wxConvUTF8)));
	neat->TrainData().LoadFromOneFolder(std::string(dlg.GetPath().mb_str(wxConvUTF8)));
	wxMessageDialog *dial = new wxMessageDialog(NULL,
		wxT("sukses!"), wxT("Info"), wxOK);
	dial->ShowModal();

}
void cMain::buttonLoadValidationDataClickedNEAT(wxCommandEvent &event) {
	if (neat == nullptr) {
		wxMessageDialog *dial = new wxMessageDialog(NULL,
			wxT("buat structure terlebih dahulu!"), wxT("Info"), wxOK);
		dial->ShowModal();
		return;
	}
	wxDirDialog dlg(NULL, "Choose input directory", "",
		wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);
	if (dlg.ShowModal() == wxID_CANCEL)
		return;
	neat->ValidationData().LoadFromOneFolder(std::string(dlg.GetPath().mb_str(wxConvUTF8)));
	wxMessageDialog *dial = new wxMessageDialog(NULL,
		wxT("sukses!"), wxT("Info"), wxOK);
	dial->ShowModal();
}
void cMain::buttonLoadTestDataClickedNEAT(wxCommandEvent &event) {
	if (neat == nullptr) {
		wxMessageDialog *dial = new wxMessageDialog(NULL,
			wxT("buat structure terlebih dahulu!"), wxT("Info"), wxOK);
		dial->ShowModal();
		return;
	}
	wxDirDialog dlg(NULL, "Choose input directory", "",
		wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);
	if (dlg.ShowModal() == wxID_CANCEL)
		return;
	test.LoadFromOneFolder(std::string(dlg.GetPath().mb_str(wxConvUTF8)));
	wxMessageDialog *dial = new wxMessageDialog(NULL,
		wxT("sukses!"), wxT("Info"), wxOK);
	dial->ShowModal();
}
void cMain::buttonLoadTest1ClassDataClickedNEAT(wxCommandEvent &event) {
	if (neat == nullptr) {
		wxMessageDialog *dial = new wxMessageDialog(NULL,
			wxT("buat structure terlebih dahulu!"), wxT("Info"), wxOK);
		dial->ShowModal();
		return;
	}
	if (text1ClassNEAT->GetValue() == "") {
		wxMessageDialog *dial = new wxMessageDialog(NULL,
			wxT("set index kelas terlebih dahulu!"), wxT("Info"), wxOK);
		dial->ShowModal();
		return;
	}
	wxDirDialog dlg(NULL, "Choose input directory", "",
		wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);
	if (dlg.ShowModal() == wxID_CANCEL)
		return;
	test.readFolder(std::string(dlg.GetPath().mb_str(wxConvUTF8)), wxAtoi(text1ClassNEAT->GetValue()));
	wxMessageDialog *dial = new wxMessageDialog(NULL,
		wxT("sukses!"), wxT("Info"), wxOK);
	dial->ShowModal();
}
void cMain::buttonSetLearningRateClickedNEAT(wxCommandEvent &event) {
	if (neat == nullptr) {
		wxMessageDialog *dial = new wxMessageDialog(NULL,
			wxT("error!"), wxT("Info"), wxOK);
		dial->ShowModal();
		return;
	}
	for (size_t i = 0; i < neat->population.size(); ++i) {
		textSetLearningRateNEAT->GetValue().ToDouble(&neat->population[i]->learning_rate);
	}
		wxMessageDialog *dial = new wxMessageDialog(NULL,
			wxT("sukses"), wxT("Info"), wxOK);
		dial->ShowModal();
}
void cMain::buttonSetStructureClickedNEAT(wxCommandEvent &event) {
	if (neat != nullptr) {
		delete neat;
		neat = nullptr;
	}
	neat = new NEAT(wxAtoi(textNumInputNEAT->GetValue()), wxAtoi(textNumHiddenNEAT->GetValue()), wxAtoi(textNumOutputNEAT->GetValue()), wxAtoi(textNumPopulationNEAT->GetValue()));
	wxMessageDialog *dial = new wxMessageDialog(NULL,
		wxT("sukses"), wxT("Info"), wxOK);
	dial->ShowModal();
}

void cMain::buttonClearTestDataNEATClicked(wxCommandEvent &event) {
	test.data.clear();
	test.data.shrink_to_fit();
	wxMessageDialog *dial = new wxMessageDialog(NULL,
		wxT("sukses"), wxT("Info"), wxOK);
	dial->ShowModal();
}

void cMain::buttonResetLayer(wxCommandEvent &event) {
	convolution_layer *temp = CNN;
	CNN = new convolution_layer(0.001, 0.99, false);
	delete temp;
}

void cMain::buttonResetStructureClicked(wxCommandEvent &event) {
	NEAT *temp = neat;
	neat = nullptr;
	delete temp;
}

void cMain::buttonPredictNEAT(wxCommandEvent &event) {
	wxFileDialog
		openFileDialog(this, _("Open Img FILE"), "", "",
			"*.jpg", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (openFileDialog.ShowModal() == wxID_CANCEL)
		return;
	std::string str = std::string(openFileDialog.GetPath().mb_str(wxConvUTF8));
	PrepareInput predictFile;
	predictFile.loadImg(str);
	std::vector<std::string> data = { "pesawat","kapak","buku","kucing","gitar","pelangi","stroberi","mesin cuci" };
	size_t index = 0;
	double fitness = 0.0;
	for (size_t i = 0; i < neat->population.size(); ++i) {
		if (neat->population[i]->getFitness() > fitness) {
			index = i;
			fitness = neat->population[i]->getFitness();
		}
	}
	int idx = neat->population[index]->predict2(predictFile.data[0]);
	neat->population[index]->fitness = fitness;
	*outputNEAT << data[idx] << "\n";
	
}

void cMain::buttonPredict(wxCommandEvent &event) {
	wxFileDialog
		openFileDialog(this, _("Open Img FILE"), "", "",
			"*.jpg", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (openFileDialog.ShowModal() == wxID_CANCEL)
		return;
	std::string str = std::string(openFileDialog.GetPath().mb_str(wxConvUTF8));
	std::vector<std::string> data = { "pesawat","kapak","buku","kucing","gitar","pelangi","stroberi","mesin cuci" };
	InputFile predictFile;
	predictFile.loadImage(str);
	int idx = CNN->predict(predictFile.data[0].inputData, { 0,0,0,0,0,0 });
	*text << data[idx] << "\n";
}