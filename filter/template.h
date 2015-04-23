#ifndef __TEMPLATE_H__
#define __TEMPLATE_H__

const char *header = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\
<gnm:Workbook xmlns:gnm=\"http://www.gnumeric.org/v10.dtd\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:schemaLocation=\"http://www.gnumeric.org/v9.xsd\">\n\
  <gnm:Version Epoch=\"1\" Major=\"12\" Minor=\"18\" Full=\"1.12.18\"/>\n\
  <gnm:Attributes>\n\
    <gnm:Attribute>\n\
      <gnm:name>WorkbookView::show_horizontal_scrollbar</gnm:name>\n\
      <gnm:value>TRUE</gnm:value>\n\
    </gnm:Attribute>\n\
    <gnm:Attribute>\n\
      <gnm:name>WorkbookView::show_vertical_scrollbar</gnm:name>\n\
      <gnm:value>TRUE</gnm:value>\n\
    </gnm:Attribute>\n\
    <gnm:Attribute>\n\
      <gnm:name>WorkbookView::show_notebook_tabs</gnm:name>\n\
      <gnm:value>TRUE</gnm:value>\n\
    </gnm:Attribute>\n\
    <gnm:Attribute>\n\
      <gnm:name>WorkbookView::do_auto_completion</gnm:name>\n\
      <gnm:value>TRUE</gnm:value>\n\
    </gnm:Attribute>\n\
    <gnm:Attribute>\n\
      <gnm:name>WorkbookView::is_protected</gnm:name>\n\
      <gnm:value>FALSE</gnm:value>\n\
    </gnm:Attribute>\n\
  </gnm:Attributes>\n\
  <office:document-meta xmlns:office=\"urn:oasis:names:tc:opendocument:xmlns:office:1.0\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" xmlns:dc=\"http://purl.org/dc/elements/1.1/\" xmlns:meta=\"urn:oasis:names:tc:opendocument:xmlns:meta:1.0\" xmlns:ooo=\"http://openoffice.org/2004/office\" office:version=\"1.2\">\n\
    <office:meta>\n";

//								   yyyy-mm-ddThh:mm:ssZ    
const char *date = "      <dc:date>%02d-%02d-%02dT%02d:%02d:%02dZ</dc:date>\n\
    <meta:creation-date>%02d-%02d-%02dT%02d:%02d:%02dZ</meta:creation-date>\n";

const char *end_header = "    </office:meta>\n\
  </office:document-meta>\n\
  <gnm:Calculation ManualRecalc=\"0\" EnableIteration=\"1\" MaxIterations=\"100\" IterationTolerance=\"0.001\" FloatRadix=\"2\" FloatDigits=\"53\"/>\n\
  <gnm:SheetNameIndex>\n\
    <gnm:SheetName gnm:Cols=\"256\" gnm:Rows=\"65536\">Sheet1</gnm:SheetName>\n\
  </gnm:SheetNameIndex>\n\
  <gnm:Geometry Width=\"1020\" Height=\"378\"/>\n\
  <gnm:Sheets>\n\
    <gnm:Sheet DisplayFormulas=\"0\" HideZero=\"0\" HideGrid=\"0\" HideColHeader=\"0\" HideRowHeader=\"0\" DisplayOutlines=\"1\" OutlineSymbolsBelow=\"1\" OutlineSymbolsRight=\"1\" Visibility=\"GNM_SHEET_VISIBILITY_VISIBLE\" GridColor=\"0:0:0\">\n\
      <gnm:Name>Sheet1</gnm:Name>\n";

//numero maximo de colunas e linhas utilizadas na tabela, comecando do 0
// -> se 4 colunas e 3 linhas entao MaxCol = 3 e MaxRow = 2
const char *sheet_dim = "      <gnm:MaxCol>%d</gnm:MaxCol>\n\
      <gnm:MaxRow>%d</gnm:MaxRow>\n";
      
const char *sheet_info = "      <gnm:Zoom>1</gnm:Zoom>\n\
      <gnm:Names>\n\
        <gnm:Name>\n\
          <gnm:name>Print_Area</gnm:name>\n\
          <gnm:value>#REF!</gnm:value>\n\
          <gnm:position>A1</gnm:position>\n\
        </gnm:Name>\n\
        <gnm:Name>\n\
          <gnm:name>Sheet_Title</gnm:name>\n\
          <gnm:value>&quot;Sheet1&quot;</gnm:value>\n\
          <gnm:position>A1</gnm:position>\n\
        </gnm:Name>\n\
      </gnm:Names>\n\
      <gnm:PrintInformation>\n\
        <gnm:Margins>\n\
          <gnm:top Points=\"120\" PrefUnit=\"mm\"/>\n\
          <gnm:bottom Points=\"120\" PrefUnit=\"mm\"/>\n\
          <gnm:left Points=\"72\" PrefUnit=\"mm\"/>\n\
          <gnm:right Points=\"72\" PrefUnit=\"mm\"/>\n\
          <gnm:header Points=\"72\" PrefUnit=\"mm\"/>\n\
          <gnm:footer Points=\"72\" PrefUnit=\"mm\"/>\n\
        </gnm:Margins>\n\
        <gnm:Scale type=\"percentage\" percentage=\"100\"/>\n\
        <gnm:vcenter value=\"0\"/>\n\
        <gnm:hcenter value=\"0\"/>\n\
        <gnm:grid value=\"0\"/>\n\
        <gnm:even_if_only_styles value=\"0\"/>\n\
        <gnm:monochrome value=\"0\"/>\n\
        <gnm:draft value=\"0\"/>\n\
        <gnm:titles value=\"0\"/>\n\
        <gnm:do_not_print value=\"0\"/>\n\
        <gnm:print_range value=\"GNM_PRINT_ACTIVE_SHEET\"/>\n\
        <gnm:order>d_then_r</gnm:order>\n\
        <gnm:orientation>portrait</gnm:orientation>\n\
        <gnm:Header Left=\"\" Middle=\"&amp;[TAB]\" Right=\"\"/>\n\
        <gnm:Footer Left=\"\" Middle=\"Page &amp;[PAGE]\" Right=\"\"/>\n\
        <gnm:paper>na_letter</gnm:paper>\n\
        <gnm:comments placement=\"GNM_PRINT_COMMENTS_IN_PLACE\"/>\n\
        <gnm:errors PrintErrorsAs=\"GNM_PRINT_ERRORS_AS_DISPLAYED\"/>\n\
      </gnm:PrintInformation>\n\
      <gnm:Styles>\n\
        <gnm:StyleRegion startCol=\"0\" startRow=\"0\" endCol=\"255\" endRow=\"65535\">\n\
          <gnm:Style HAlign=\"GNM_HALIGN_GENERAL\" VAlign=\"GNM_VALIGN_BOTTOM\" WrapText=\"0\" ShrinkToFit=\"0\" Rotation=\"0\" Shade=\"0\" Indent=\"0\" Locked=\"1\" Hidden=\"0\" Fore=\"0:0:0\" Back=\"FFFF:FFFF:FFFF\" PatternColor=\"0:0:0\" Format=\"General\">\n\
            <gnm:Font Unit=\"10\" Bold=\"0\" Italic=\"0\" Underline=\"0\" StrikeThrough=\"0\" Script=\"0\">Sans</gnm:Font>\n\
          </gnm:Style>\n\
        </gnm:StyleRegion>\n\
      </gnm:Styles>\n\
      <gnm:Cols DefaultSizePts=\"48\"/>\n\
      <gnm:Rows DefaultSizePts=\"12.75\"/>\n\
      <gnm:Selections CursorCol=\"0\" CursorRow=\"0\">\n\
        <gnm:Selection startCol=\"0\" startRow=\"0\" endCol=\"0\" endRow=\"0\"/>\n\
      </gnm:Selections>\n";
      
const char *sheet_end = "      <gnm:SheetLayout TopLeft=\"A1\"/>\n\
      <gnm:Solver ModelType=\"0\" ProblemType=\"0\" MaxTime=\"60\" MaxIter=\"1000\" NonNeg=\"1\" Discr=\"0\" AutoScale=\"0\" ProgramR=\"0\"/>\n\
    </gnm:Sheet>\n\
  </gnm:Sheets>\n\
  <gnm:UIData SelectedTab=\"0\"/>\n\
</gnm:Workbook>\n";

#endif
