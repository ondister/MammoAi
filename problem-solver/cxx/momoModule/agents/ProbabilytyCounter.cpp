/*
* This source file is part of an OSTIS project. For the latest info, see http://ostis.net
* Distributed under the MIT License
* (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
*/

#include <sc-memory/cpp/sc_stream.hpp>
#include <sc-kpm/sc-agents-common/utils/IteratorUtils.hpp>
#include <sc-kpm/sc-agents-common/utils/GenerationUtils.hpp>
#include <sc-kpm/sc-agents-common/utils/AgentUtils.hpp>
#include <sc-kpm/sc-agents-common/utils/CommonUtils.hpp>
#include <string>
#include <iostream>
#include <vector>

#include "ProbabilytyCounter.hpp"
#include "keynodes/keynodes.hpp"

using namespace std;
using namespace utils;

namespace momoModule {

	vector <vector<vector < vector < vector < ScAddr>>>>>		nosological_forms(ScMemoryContext* ms_context) {
		vector <ScAddr> forms;
		ScIterator3Ptr iterator3 = ms_context->Iterator3(Keynodes::concept_nosological_form, ScType::EdgeAccessConstPosPerm, ScType::Unknown);
		while (iterator3->Next()) {
			forms.push_back(iterator3->Get(2));
		}
		vector <ScAddr> nosologic_forms;
		for (int i = 0; i < forms.size(); i++) {
			//ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, forms[i]);
			ScIterator3Ptr nosoIT = ms_context->Iterator3(forms[i], ScType::EdgeAccessConstPosPerm, ScType::Unknown);
			while (nosoIT->Next()) {
				nosologic_forms.push_back(nosoIT->Get(2));
			}
		}
		vector <vector<vector < vector < vector < ScAddr>>>>>			nosologic_forms_v;
		///////////////////////////////////////////////////////
		for (int i = 0; i < nosologic_forms.size(); i++) {
			vector <vector<vector < vector < ScAddr >> >>				nosologic_form_v;
			vector <ScAddr> nf;
			vector <vector<ScAddr>> nf1;
			vector <vector<vector < ScAddr>>>				nf2;
			nf.push_back(nosologic_forms[i]);
			nf1.push_back(nf);
			nf2.push_back(nf1);
			nosologic_form_v.push_back(nf2);


			//ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, nosologic_forms[i]);
			ScAddr attribute;
			ScIterator5Ptr atrIT = ms_context->Iterator5(nosologic_forms[i], ScType::EdgeDCommonConst, ScType::Unknown, ScType::EdgeAccessConstPosPerm, Keynodes::nrel_attributes);
			SC_LOG_INFO("1")
				if (atrIT->Next()) {
					SC_LOG_INFO("2")
						attribute = atrIT->Get(2);
					//ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, attribute);
				}
			vector <ScAddr> artifacts;
			ScIterator3Ptr artIT = ms_context->Iterator3(attribute, ScType::EdgeAccessConstPosPerm, ScType::Unknown);
			while (artIT->Next()) {
				artifacts.push_back(artIT->Get(2));
			}
			vector <ScAddr> art_type;

			vector <vector<vector < ScAddr>>>				artifacts_v;
			for (int j = 0; j < artifacts.size(); j++) {

				ScIterator3Ptr arttype = ms_context->Iterator3(ScType::Unknown, ScType::EdgeAccessConstPosPerm, artifacts[j]);
				while (arttype->Next()) {
					art_type.push_back(arttype->Get(0));
				}
			}

			for (int j = 0; j < artifacts.size(); j++) {
				vector <vector<ScAddr>> artifact;
				vector <ScAddr> a_type_v;
				a_type_v.push_back(artifacts[j]);
				artifact.push_back(a_type_v);
				//ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, art_type[j]);


				SC_LOG_INFO("/////")
					ScIterator5Ptr shapeIT = ms_context->Iterator5(artifacts[j], ScType::EdgeDCommonConst, ScType::Unknown, ScType::EdgeAccessConstPosPerm, Keynodes::nrel_shape_of_mass);
				vector <ScAddr> shape;
				while (shapeIT->Next()) {
					shape.push_back(shapeIT->Get(2));
				}


				vector <ScAddr> shape_type;
				for (int k = 0; k < shape.size(); k++) {
					ScIterator3Ptr shapeTypeIT = ms_context->Iterator3(ScType::Unknown, ScType::EdgeAccessConstPosPerm, shape[k]);
					while (shapeTypeIT->Next()) {
						shape_type.push_back(shapeTypeIT->Get(0));
					}
				}
				for (int k = 0; k < shape_type.size(); k++) {
					if (shape_type[k].IsValid()) {
						string shape_str = CommonUtils::getIdtfValue(ms_context, shape_type[k], Keynodes::nrel_main_idtf);
						SC_LOG_INFO(shape_str)
					}
				}
				artifact.push_back(shape);

				//края

				ScIterator5Ptr margIT = ms_context->Iterator5(artifacts[j], ScType::EdgeDCommonConst, ScType::Unknown, ScType::EdgeAccessConstPosPerm, Keynodes::nrel_margins_of_mass);
				vector <ScAddr> marg;
				while (margIT->Next()) {
					marg.push_back(margIT->Get(2));
				}


				vector <ScAddr> marg_type;
				for (int k = 0; k < marg.size(); k++) {
					ScIterator3Ptr margTypeIT = ms_context->Iterator3(ScType::Unknown, ScType::EdgeAccessConstPosPerm, marg[k]);
					while (margTypeIT->Next()) {
						marg_type.push_back(margTypeIT->Get(0));
					}
				}
				for (int k = 0; k < marg_type.size(); k++) {
					if (marg_type[k].IsValid()) {
						string marg_str = CommonUtils::getIdtfValue(ms_context, marg_type[k], Keynodes::nrel_main_idtf);
						SC_LOG_INFO(marg_str)
					}
				}
				artifact.push_back(marg);
				//плотность

				ScIterator5Ptr denIT = ms_context->Iterator5(artifacts[j], ScType::EdgeDCommonConst, ScType::Unknown, ScType::EdgeAccessConstPosPerm, Keynodes::nrel_mass_density);
				vector <ScAddr> den;
				while (denIT->Next()) {
					den.push_back(denIT->Get(2));
				}


				vector <ScAddr> den_type;
				for (int k = 0; k < den.size(); k++) {
					ScIterator3Ptr denTypeIT = ms_context->Iterator3(ScType::Unknown, ScType::EdgeAccessConstPosPerm, den[k]);
					while (denTypeIT->Next()) {
						den_type.push_back(denTypeIT->Get(0));
					}
				}
				for (int k = 0; k < den_type.size(); k++) {
					if (den_type[k].IsValid()) {
						string den_str = CommonUtils::getIdtfValue(ms_context, den_type[k], Keynodes::nrel_main_idtf);
						SC_LOG_INFO(den_str)
					}
				}
				artifact.push_back(den);
				//размер

				ScIterator5Ptr sizeIT = ms_context->Iterator5(artifacts[j], ScType::EdgeDCommonConst, ScType::Unknown, ScType::EdgeAccessConstPosPerm, Keynodes::nrel_artifact_size);
				vector <ScAddr> size;
				while (sizeIT->Next()) {
					size.push_back(sizeIT->Get(2));
				}

				for (int k = 0; k < size.size(); k++) {
					if (size[k].IsValid()) {
						string size_str = CommonUtils::getIdtfValue(ms_context, artifacts[j], Keynodes::nrel_artifact_size);
						SC_LOG_INFO(size_str)
					}
				}
				artifact.push_back(size);


				//////////////////////////кальцинаты


				ScIterator5Ptr distIT = ms_context->Iterator5(artifacts[j], ScType::EdgeDCommonConst, ScType::Unknown, ScType::EdgeAccessConstPosPerm, Keynodes::nrel_calc_distribution);
				vector <ScAddr> dist;
				while (distIT->Next()) {
					dist.push_back(distIT->Get(2));
				}


				vector <ScAddr> dist_type;
				for (int k = 0; k < dist.size(); k++) {
					ScIterator3Ptr distTypeIT = ms_context->Iterator3(ScType::Unknown, ScType::EdgeAccessConstPosPerm, dist[k]);
					while (distTypeIT->Next()) {
						dist_type.push_back(distTypeIT->Get(0));
					}
				}

				for (int k = 0; k < dist_type.size(); k++) {
					if (dist_type[k].IsValid()) {
						string dist_str = CommonUtils::getIdtfValue(ms_context, dist_type[k], Keynodes::nrel_main_idtf);
						SC_LOG_INFO(dist_str)
					}
				}
				artifact.push_back(dist);

				artifacts_v.push_back(artifact);
			}

			nosologic_form_v.push_back(artifacts_v);
			nosologic_forms_v.push_back(nosologic_form_v);


		}////////////////////////////////////////
		return	nosologic_forms_v;
	}

	void read_5_vector(vector < vector < vector < vector < vector < ScAddr >>>>> forms, ScMemoryContext* ms_context) {

		for (int a = 0; a < forms.size(); a++) {
			for (int b = 0; b < forms[a].size(); b++) {
				for (int c = 0; c < forms[a][b].size(); c++) {
					for (int d = 0; d < forms[a][b][c].size(); d++) {
						for (int e = 0; e < forms[a][b][c][d].size(); e++) {
							ScAddr node = forms[a][b][c][d][e];
							if (node.IsValid()) {
								string strtemp =
									"[" + to_string(a) + "] " + "[" + to_string(b) + "] " + "[" + to_string(c) + "] " + "[" + to_string(d) + "] " +
									"[" + to_string(e) + "]";
                                                                //SC_LOG_INFO(strtemp);
								ScAddr type;
								ScIterator3Ptr TypeIT = ms_context->Iterator3(ScType::Unknown,
									ScType::EdgeAccessConstPosPerm,
									node);
								while (TypeIT->Next()) {
									type = TypeIT->Get(0);
								}
								string strin = CommonUtils::getIdtfValue(ms_context, type, Keynodes::nrel_main_idtf);
                                                                //SC_LOG_INFO(strin);
								string str = CommonUtils::getIdtfValue(ms_context, node, Keynodes::nrel_probability);
                                                                //SC_LOG_INFO(str);
							}
						}
					}
				}
			}
		}


	}

	vector <vector<vector < ScAddr>>>study_artefacts(ScMemoryContext* ms_context, ScAddr spatials) {
		vector <ScAddr> artifacts;
		ScIterator3Ptr artIT = ms_context->Iterator3(spatials, ScType::EdgeAccessConstPosPerm, ScType::Unknown);
		while (artIT->Next()) {
			artifacts.push_back(artIT->Get(2));
		}
		vector <ScAddr> art_type;


		vector <vector<vector < ScAddr>>> artifacts_v;
		for (int j = 0; j < artifacts.size(); j++) {
			ScIterator3Ptr arttype = ms_context->Iterator3(ScType::Unknown, ScType::EdgeAccessConstPosPerm, artifacts[j]);
			while (arttype->Next()) {
                            if(ms_context->HelperCheckEdge(Keynodes::concept_artifact_type, arttype->Get(0), ScType::EdgeAccessConstPosPerm)){
				art_type.push_back(arttype->Get(0));
                                string strin = CommonUtils::getIdtfValue(ms_context, arttype->Get(0), Keynodes::nrel_main_idtf);
                                SC_LOG_INFO(strin);
                                SC_LOG_INFO("arttype");
                            }
			}
		}

		for (int j = 0; j < artifacts.size(); j++) {
			vector <vector<ScAddr>> artifact;
			vector <ScAddr> a_type_v;
			a_type_v.push_back(artifacts[j]);
			artifact.push_back(a_type_v);
			//ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, art_type[j]);


                        //SC_LOG_INFO("/////")
				ScIterator5Ptr shapeIT = ms_context->Iterator5(artifacts[j], ScType::EdgeDCommonConst, ScType::Unknown, ScType::EdgeAccessConstPosPerm, Keynodes::nrel_shape_of_mass);
			vector <ScAddr> shape;
			while (shapeIT->Next()) {
				shape.push_back(shapeIT->Get(2));
			}


			vector <ScAddr> shape_type;
			for (int k = 0; k < shape.size(); k++) {
				ScIterator3Ptr shapeTypeIT = ms_context->Iterator3(ScType::Unknown, ScType::EdgeAccessConstPosPerm, shape[k]);
				while (shapeTypeIT->Next()) {
					shape_type.push_back(shapeTypeIT->Get(0));
				}
			}
			for (int k = 0; k < shape_type.size(); k++) {
				if (shape_type[k].IsValid()) {
                                        //SC_LOG_INFO("shape");

					string shape_str = CommonUtils::getIdtfValue(ms_context, shape_type[k], Keynodes::nrel_main_idtf);
                                        //SC_LOG_INFO(shape_str);
				}
			}
			artifact.push_back(shape);

			//края

			ScIterator5Ptr margIT = ms_context->Iterator5(artifacts[j], ScType::EdgeDCommonConst, ScType::Unknown, ScType::EdgeAccessConstPosPerm, Keynodes::nrel_margins_of_mass);
			vector <ScAddr> marg;
			while (margIT->Next()) {
				marg.push_back(margIT->Get(2));
			}


			vector <ScAddr> marg_type;
			for (int k = 0; k < marg.size(); k++) {
				ScIterator3Ptr margTypeIT = ms_context->Iterator3(ScType::Unknown, ScType::EdgeAccessConstPosPerm, marg[k]);
				while (margTypeIT->Next()) {
					marg_type.push_back(margTypeIT->Get(0));
				}
			}
			for (int k = 0; k < marg_type.size(); k++) {
				if (marg_type[k].IsValid()) {
                                        //SC_LOG_INFO("margins");
					string marg_str = CommonUtils::getIdtfValue(ms_context, marg_type[k], Keynodes::nrel_main_idtf);
                                        //SC_LOG_INFO(marg_str)
				}
			}
			artifact.push_back(marg);
			//плотность

			ScIterator5Ptr denIT = ms_context->Iterator5(artifacts[j], ScType::EdgeDCommonConst, ScType::Unknown, ScType::EdgeAccessConstPosPerm, Keynodes::nrel_mass_density);
			vector <ScAddr> den;
			while (denIT->Next()) {
				den.push_back(denIT->Get(2));
			}


			vector <ScAddr> den_type;
			for (int k = 0; k < den.size(); k++) {
				ScIterator3Ptr denTypeIT = ms_context->Iterator3(ScType::Unknown, ScType::EdgeAccessConstPosPerm, den[k]);
				while (denTypeIT->Next()) {
					den_type.push_back(denTypeIT->Get(0));
				}
			}
			for (int k = 0; k < den_type.size(); k++) {
				if (den_type[k].IsValid()) {
                                        //SC_LOG_INFO("density");
					string den_str = CommonUtils::getIdtfValue(ms_context, den_type[k], Keynodes::nrel_main_idtf);
                                        //SC_LOG_INFO(den_str)
				}
			}
			artifact.push_back(den);
			//размер

			ScIterator5Ptr sizeIT = ms_context->Iterator5(artifacts[j], ScType::EdgeDCommonConst, ScType::Unknown, ScType::EdgeAccessConstPosPerm, Keynodes::nrel_artifact_size);
			vector <ScAddr> size;
			while (sizeIT->Next()) {
				size.push_back(sizeIT->Get(2));
			}

			for (int k = 0; k < size.size(); k++) {
				if (size[k].IsValid()) {
                                        //SC_LOG_INFO("size");
					string size_str = CommonUtils::getIdtfValue(ms_context, artifacts[j], Keynodes::nrel_artifact_size);
                                        //SC_LOG_INFO(size_str)
				}
			}
			artifact.push_back(size);


			//////////////////////////кальцинаты


			ScIterator5Ptr distIT = ms_context->Iterator5(artifacts[j], ScType::EdgeDCommonConst, ScType::Unknown, ScType::EdgeAccessConstPosPerm, Keynodes::nrel_calc_distribution);
			vector <ScAddr> dist;
			while (distIT->Next()) {
				dist.push_back(distIT->Get(2));
			}


			vector <ScAddr> dist_type;
			for (int k = 0; k < dist.size(); k++) {
				ScIterator3Ptr distTypeIT = ms_context->Iterator3(ScType::Unknown, ScType::EdgeAccessConstPosPerm, dist[k]);
				while (distTypeIT->Next()) {
					dist_type.push_back(distTypeIT->Get(0));
				}
			}

			for (int k = 0; k < dist_type.size(); k++) {
				if (dist_type[k].IsValid()) {
                                        //SC_LOG_INFO("dist");
					string dist_str = CommonUtils::getIdtfValue(ms_context, dist_type[k], Keynodes::nrel_main_idtf);
                                        //SC_LOG_INFO(dist_str)
				}
			}
			artifact.push_back(dist);

			artifacts_v.push_back(artifact);
		}

                return	artifacts_v;
	}

        void read_3_vector( vector < vector < vector < ScAddr >>> study, ScMemoryContext* ms_context){
            for (int c = 0; c < study.size(); c++) {
                    for (int d = 0; d < study[c].size(); d++) {
                            for (int e = 0; e < study[c][d].size(); e++) {
                                    ScAddr node = study[c][d][e];
                                    if (node.IsValid()) {
                                            string strtemp = "[" + to_string(c) + "] " + "[" + to_string(d) + "] " + "[" + to_string(e) + "]";
                                           // SC_LOG_INFO(strtemp);
                                            ScAddr type;
                                            ScIterator3Ptr TypeIT = ms_context->Iterator3(ScType::Unknown, ScType::EdgeAccessConstPosPerm, node);
                                            while (TypeIT->Next()) {
                                                    type = TypeIT->Get(0);
                                            }
                                            string strin = CommonUtils::getIdtfValue(ms_context, type, Keynodes::nrel_main_idtf);
                                            //SC_LOG_INFO(strin);
                                            if(ms_context->HelperCheckEdge(Keynodes::concept_mass, type,ScType::EdgeAccessConstPosPerm)){
                                                //SC_LOG_INFO("artifact");
                                            }
                                           /* if(d==0){
                                                SC_LOG_INFO("0");
                                                ScIterator5Ptr shapeIT = ms_context->Iterator5(type, ScType::EdgeDCommonConst, ScType::Unknown, ScType::EdgeAccessConstPosPerm, Keynodes::nrel_shape_of_mass);

                                             while (shapeIT->Next()) {
                                                 if(shapeIT->Get(2).IsValid()){
                                                 SC_LOG_INFO("mass");
                                                 }
                                             }



                                           ScIterator5Ptr shapecIT = ms_context->Iterator5(type, ScType::EdgeDCommonConst, ScType::Unknown, ScType::EdgeAccessConstPosPerm, Keynodes::nrel_calc_distribution);

                                        while (shapecIT->Next()) {
                                            if(shapecIT->Get(2).IsValid()){
                                                SC_LOG_INFO("calc");
                                                     }
                                        }


                                            }*/

                                    }
                            }
                    }
            }

        }

        float probability_count(ScMemoryContext* ms_context, ScAddr nos_form){
        //ScAddr nos_form=forms[a][0][0][0][0];
        string nos_form_str = CommonUtils::getIdtfValue(ms_context, nos_form, Keynodes::nrel_main_idtf);
        //SC_LOG_INFO(nos_form_str);

        ScIterator5Ptr prIT = ms_context->Iterator5(nos_form, ScType::EdgeDCommonConst, ScType::Unknown, ScType::EdgeAccessConstPosPerm, Keynodes::nrel_probability);
                ScAddr probability;
                while (prIT->Next()) {
                                probability = prIT->Get(2);
                }
        ScAddr form_probability;
        ScIterator3Ptr proIT = ms_context->Iterator3(probability, ScType::EdgeAccessConstPosPerm, ScType::Unknown);
        while (proIT->Next()) {
                form_probability=proIT->Get(2);
        }
        string value = CommonUtils::readString(ms_context, form_probability);
        SC_LOG_INFO(value);
        float form_pr = stof(value);
        //probability_f=(form_pr)/100;
        SC_LOG_INFO(to_string(form_pr));
        return form_pr/100;
        }
        SC_AGENT_IMPLEMENTATION(ProbabilytyCounter)
	{
		if (!edgeAddr.IsValid())
			return SC_RESULT_ERROR;


		SC_LOG_INFO("----------counter begin----------");
		ScAddr questionNode = ms_context->GetEdgeTarget(edgeAddr);
		ScAddr spatials = IteratorUtils::getFirstFromSet(ms_context.get(), questionNode);
		if (!spatials.IsValid())
			return SC_RESULT_ERROR_INVALID_PARAMS;
		ScAddr answer = ms_context->CreateNode(ScType::NodeConstStruct);

		vector<vector<vector<vector<vector<ScAddr>>>>> forms = nosological_forms(ms_context.get());
		read_5_vector(forms, ms_context.get());
		vector<vector<vector<ScAddr>>>study = study_artefacts(ms_context.get(), spatials);
                read_3_vector(study, ms_context.get());
string report;
                for (int a = 0; a < forms.size(); a++) {
                    float probability_f=0;
                        for (int b = 0; b < forms[a].size(); b++) {
                                for (int c = 0; c < forms[a][b].size(); c++) {
                                        for (int d = 0; d < forms[a][b][c].size(); d++) {
                                                for (int e = 0; e < forms[a][b][c][d].size(); e++) {
                                                    ScAddr node = forms[a][b][c][d][e];
                                                    if (node.IsValid()) {
                                                    if(b==0&&c==0&&d==0&&e==0){
                                                    ScAddr nos_form=forms[a][0][0][0][0];
                                                    float value=probability_count(ms_context.get(),nos_form);
                                                   string nos_form_str = CommonUtils::getIdtfValue(ms_context.get(), nos_form, Keynodes::nrel_main_idtf);
                                                    SC_LOG_INFO(nos_form_str);
                                                    report=report+nos_form_str+"-";
/*
                                                    ScIterator5Ptr prIT = ms_context->Iterator5(nos_form, ScType::EdgeDCommonConst, ScType::Unknown, ScType::EdgeAccessConstPosPerm, Keynodes::nrel_probability);
                                                            ScAddr probability;
                                                            while (prIT->Next()) {
                                                                            probability = prIT->Get(2);
                                                            }
                                                    ScAddr form_probability;
                                                    ScIterator3Ptr proIT = ms_context->Iterator3(probability, ScType::EdgeAccessConstPosPerm, ScType::Unknown);
                                                    while (proIT->Next()) {
                                                            form_probability=proIT->Get(2);
                                                    }
                                                    string value = CommonUtils::readString(ms_context.get(), form_probability);
                                                    SC_LOG_INFO(value);
                                                    float form_pr = stof(value);*/
                                                    probability_f=value;
                                                    SC_LOG_INFO(to_string(probability_f));
                                                    }


                                                    //if(c==0&&d==0&&e==0){
                                                        for(int f=0; f<study.size();f++){
                                                            SC_LOG_INFO("1f");

                                                            //если образование или кальцинат то плюс вероятность study[f][0][0]


                                                    //for(int g=0; g<study[f].size(); g++){
                                                       // SC_LOG_INFO("1g");
                                                       // string s = to_string(study.size())+ "  -  "+to_string(study[f].size());
                                                        //SC_LOG_INFO(s);

                                                        ScAddr nodeF=forms[a][b][c][d][e];
                                                        //SC_LOG_INFO("1.5g");
                                                        //if(f==0&&g==5){break;}
                                                        //ScAddr nodeS=study[f][g][0];
                                                       // SC_LOG_INFO("2g");
                                                        //if(nodeF.IsValid()&&study[f][g][0].IsValid()){
                                                          //  SC_LOG_INFO("3g");
                                                            ScAddr nodeS=study[f][0][0];
                                                           // SC_LOG_INFO("3.5g");

                                                        string strforms =
                                                                "[" + to_string(a) + "] " + "[" + to_string(b) + "] " + "[" + to_string(c) + "] " + "[" + to_string(d) + "] " +
                                                                "[" + to_string(e) + "]";
                                                        SC_LOG_INFO(strforms);
                                                        string strstudy =
                                                                "[" + to_string(0) + "] " + "[" + to_string(0) + "] " + "[" + to_string(f) + "] " + "[" + to_string(0) + "] " +
                                                                "[" + to_string(0) + "]";
                                                        SC_LOG_INFO(strstudy);



                                                        ScAddr typeF;
                                                        ScIterator3Ptr TypeFIT = ms_context->Iterator3(ScType::Unknown,
                                                                ScType::EdgeAccessConstPosPerm,
                                                                nodeF);
                                                        while (TypeFIT->Next()) {
                                                                typeF = TypeFIT->Get(0);
                                                        }
                                                        string strinF = CommonUtils::getIdtfValue(ms_context.get(), typeF, Keynodes::nrel_main_idtf);
                                                        SC_LOG_INFO(strinF);



                                                        ScAddr typeS;
                                                        ScIterator3Ptr TypeSIT = ms_context->Iterator3(ScType::Unknown,
                                                                ScType::EdgeAccessConstPosPerm,
                                                                nodeS);
                                                        while (TypeSIT->Next()) {
                                                                typeS = TypeSIT->Get(0);
                                                        }
                                                        string strinS = CommonUtils::getIdtfValue(ms_context.get(), typeS, Keynodes::nrel_main_idtf);
                                                        SC_LOG_INFO(strinS);
                                                        ///////////////////////////////////////////////////
                                                        if(f==1){
                                                        strstudy =
                                                                "[" + to_string(0) + "] " + "[" + to_string(0) + "] " + "[" + to_string(f) + "] " + "[" + to_string(1) + "] " +
                                                                "[" + to_string(0) + "]";
                                                        SC_LOG_INFO(strforms);
                                                        SC_LOG_INFO(strstudy);


                                                        if(study[f][1][0].IsValid()){
                                                        nodeS=study[f][1][0];
                                                        ScAddr typeS;
                                                        ScIterator3Ptr TypeSIT = ms_context->Iterator3(ScType::Unknown,
                                                                ScType::EdgeAccessConstPosPerm,
                                                                nodeS);
                                                        while (TypeSIT->Next()) {
                                                                typeS = TypeSIT->Get(0);
                                                        }
                                                        strinS = CommonUtils::getIdtfValue(ms_context.get(), typeS, Keynodes::nrel_main_idtf);
                                                        SC_LOG_INFO(strinF);
                                                        SC_LOG_INFO(strinS);
                                                        if(strinF==strinS){
                                                            string str = CommonUtils::getIdtfValue(ms_context.get(), nodeF, Keynodes::nrel_probability);
                                                            SC_LOG_INFO(str);

                                                            float form_pr = stof(str);
                                                            probability_f=probability_f*(form_pr/100);
                                                            SC_LOG_INFO(to_string(probability_f));

                                                            SC_LOG_INFO("------------------------------------------------------------------------");
                                                        }}
                                                        //////////////////////////////////////////////////////
                                                        strstudy =
                                                                "[" + to_string(0) + "] " + "[" + to_string(0) + "] " + "[" + to_string(f) + "] " + "[" + to_string(2) + "] " +
                                                                "[" + to_string(0) + "]";
                                                        SC_LOG_INFO(strforms);
                                                        SC_LOG_INFO(strstudy);

                                                        if(study[f][2][0].IsValid()){
                                                        nodeS=study[f][2][0];
                                                        ScAddr typeS;
                                                        ScIterator3Ptr TypeSIT = ms_context->Iterator3(ScType::Unknown,
                                                                ScType::EdgeAccessConstPosPerm,
                                                                nodeS);
                                                        while (TypeSIT->Next()) {
                                                                typeS = TypeSIT->Get(0);
                                                        }
                                                        strinS = CommonUtils::getIdtfValue(ms_context.get(), typeS, Keynodes::nrel_main_idtf);
                                                        SC_LOG_INFO(strinF);
                                                        SC_LOG_INFO(strinS);
                                                        if(strinF==strinS){
                                                            string str = CommonUtils::getIdtfValue(ms_context.get(), nodeF, Keynodes::nrel_probability);
                                                            SC_LOG_INFO(str);
                                                            float form_pr = stof(str);
                                                            probability_f=probability_f*(form_pr/100);
                                                            SC_LOG_INFO(to_string(probability_f));
                                                            SC_LOG_INFO("------------------------------------------------------------------------");
                                                        }}
                                                       //////////////////////////////////////////////////////////////////////////////////////////////////////////
                                                        strstudy =
                                                                "[" + to_string(0) + "] " + "[" + to_string(0) + "] " + "[" + to_string(f) + "] " + "[" + to_string(3) + "] " +
                                                                "[" + to_string(0) + "]";
                                                        SC_LOG_INFO(strforms);
                                                        SC_LOG_INFO(strstudy);

                                                        if(study[f][3][0].IsValid()){
                                                        nodeS=study[f][3][0];
                                                        ScAddr typeS;
                                                        ScIterator3Ptr TypeSIT = ms_context->Iterator3(ScType::Unknown,
                                                                ScType::EdgeAccessConstPosPerm,
                                                                nodeS);
                                                        while (TypeSIT->Next()) {
                                                                typeS = TypeSIT->Get(0);
                                                        }
                                                        strinS = CommonUtils::getIdtfValue(ms_context.get(), typeS, Keynodes::nrel_main_idtf);
                                                        SC_LOG_INFO(strinF);
                                                        SC_LOG_INFO(strinS);
                                                        if(strinF==strinS){
                                                            string str = CommonUtils::getIdtfValue(ms_context.get(), nodeF, Keynodes::nrel_probability);
                                                            SC_LOG_INFO(str);
                                                            float form_pr = stof(str);
                                                            probability_f=probability_f*(form_pr/100);
                                                            SC_LOG_INFO(to_string(probability_f));
                                                            SC_LOG_INFO("------------------------------------------------------------------------");
                                                        }}
                                                        /////////////////////////////////////////////
                                                        strstudy =
                                                                "[" + to_string(0) + "] " + "[" + to_string(0) + "] " + "[" + to_string(f) + "] " + "[" + to_string(4) + "] " +
                                                                "[" + to_string(0) + "]";
                                                        SC_LOG_INFO(strforms);
                                                        SC_LOG_INFO(strstudy);

                                                        if(study[f][4][0].IsValid()){
                                                        nodeS=study[f][4][0];
                                                        ScAddr typeS;
                                                        ScIterator3Ptr TypeSIT = ms_context->Iterator3(ScType::Unknown,
                                                                ScType::EdgeAccessConstPosPerm,
                                                                nodeS);
                                                        while (TypeSIT->Next()) {
                                                                typeS = TypeSIT->Get(0);
                                                        }
                                                        strinS = CommonUtils::getIdtfValue(ms_context.get(), typeS, Keynodes::nrel_main_idtf);
                                                       SC_LOG_INFO(strinF);
                                                       SC_LOG_INFO(strinS);
                                                       if(strinF==strinS){
                                                           string str = CommonUtils::getIdtfValue(ms_context.get(), nodeF, Keynodes::nrel_probability);
                                                           SC_LOG_INFO(str);
                                                           float form_pr = stof(str);
                                                           probability_f=probability_f*(form_pr/100);
                                                           SC_LOG_INFO(to_string(probability_f));
                                                           SC_LOG_INFO("------------------------------------------------------------------------");
                                                       }}
                                                        }
                                                        ////////////////////////////////////////////
                                                        if(f==0){
                                                        strstudy =
                                                                "[" + to_string(0) + "] " + "[" + to_string(0) + "] " + "[" + to_string(f) + "] " + "[" + to_string(5) + "] " +
                                                                "[" + to_string(0) + "]";
                                                        SC_LOG_INFO(strforms);
                                                        SC_LOG_INFO(strstudy);

                                                        if(study[f][5][0].IsValid()){
                                                        nodeS=study[f][5][0];
                                                        ScAddr typeS;
                                                        ScIterator3Ptr TypeSIT = ms_context->Iterator3(ScType::Unknown,
                                                                ScType::EdgeAccessConstPosPerm,
                                                                nodeS);
                                                        while (TypeSIT->Next()) {
                                                                typeS = TypeSIT->Get(0);
                                                        }
                                                        strinS = CommonUtils::getIdtfValue(ms_context.get(), typeS, Keynodes::nrel_main_idtf);
                                                        SC_LOG_INFO(strinF);
                                                        SC_LOG_INFO(strinS);
                                                        if(strinF==strinS){
                                                            string str = CommonUtils::getIdtfValue(ms_context.get(), nodeF, Keynodes::nrel_probability);
                                                             SC_LOG_INFO(str);
                                                             float form_pr = stof(str);
                                                             probability_f=probability_f*(form_pr/100);
                                                             SC_LOG_INFO(to_string(probability_f));
                                                            SC_LOG_INFO("------------------------------------------------------------------------");
                                                        }}
                                                        }
                                                        /////////////////////////////////////

                                                       // }
                                                        //SC_LOG_INFO("4g");

                                                   // }
                                                    }

                                                    }
                                                    /*
                                                        ScAddr node = forms[a][b][c][d][e];
                                                        if (node.IsValid()) {
                                                                string strtemp =
                                                                        "[" + to_string(a) + "] " + "[" + to_string(b) + "] " + "[" + to_string(c) + "] " + "[" + to_string(d) + "] " +
                                                                        "[" + to_string(e) + "]";
                                                                SC_LOG_INFO(strtemp);
                                                                ScAddr type;
                                                                ScIterator3Ptr TypeIT = ms_context->Iterator3(ScType::Unknown,
                                                                        ScType::EdgeAccessConstPosPerm,
                                                                        node);
                                                                while (TypeIT->Next()) {
                                                                        type = TypeIT->Get(0);
                                                                }
                                                                string strin = CommonUtils::getIdtfValue(ms_context.get(), type, Keynodes::nrel_main_idtf);
                                                                SC_LOG_INFO(strin);
                                                                string str = CommonUtils::getIdtfValue(ms_context.get(), node, Keynodes::nrel_probability);
                                                                SC_LOG_INFO(str);
                                                        }*/
                                                }
                                        }
                                }
                        }
                        probability_f*=100;
                        report = report+to_string(probability_f)+"%\n";

                }
SC_LOG_INFO(report);

ScAddr answer_link = ms_context->CreateLink();
string value = report;

ScStreamPtr stream;
stream.reset(new ScStream(value.c_str(), (sc_uint32) value.size(), SC_STREAM_FLAG_READ ));
ms_context->SetLinkContent(answer_link, *stream);



ScAddr edge_answer = ms_context->CreateEdge(ScType::EdgeDCommonConst,spatials , answer_link);

ScAddr edge_edge_answer = ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, Keynodes::nrel_study_report, edge_answer);

ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, answer_link);
ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, spatials);
ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, edge_answer);
ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, edge_edge_answer);
ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, Keynodes::nrel_study_report );



		//read_5_vector(study,ms_context.get());
/*
					for(int a=0; a<forms.size(); a++){
						for(int b=0; b<forms[a].size();b++){
							for(int c=0; c<forms[a][b].size();c++){
								for(int c1=0; c1<study.size();c1++){
									ScAddr form3=forms[a][b][c][0][0];
									ScAddr study3=study[c1][0][0];
									if (form3.IsValid()&&study3.IsValid()) {
										SC_LOG_INFO("forms");
										string strtemp =
												"[" + to_string(a) + "] " + "[" + to_string(b) + "] " + "[" +
												to_string(c) + "] " + "[" + to_string(0) + "] " + "[" +
												to_string(0) + "]";
										SC_LOG_INFO(strtemp);
										ScAddr type;
										ScIterator3Ptr TypeIT = ms_context->Iterator3(ScType::Unknown,
																					  ScType::EdgeAccessConstPosPerm,
																					  form3);
										while (TypeIT->Next()) {
											type = TypeIT->Get(0);
										}
										string strin = CommonUtils::getIdtfValue(ms_context.get(), type,
																				 Keynodes::nrel_main_idtf);
										SC_LOG_INFO(strin);
										string str = CommonUtils::getIdtfValue(ms_context.get(), form3,
																			   Keynodes::nrel_probability);
										SC_LOG_INFO(str);


										//////////////////////////////
										SC_LOG_INFO("study");
										string strtemp1 =
												"[" + to_string(a) + "] " + "[" + to_string(b) + "] " + "[" +
												to_string(c1) + "] " + "[" + to_string(0) + "] " + "[" +
												to_string(0) + "]";
										SC_LOG_INFO(strtemp1);
										ScAddr type1;
										ScIterator3Ptr TypeIT1 = ms_context->Iterator3(ScType::Unknown,
																					  ScType::EdgeAccessConstPosPerm,
																					  study3);
										while (TypeIT1->Next()) {
											type1 = TypeIT1->Get(0);
										}
										string strin1 = CommonUtils::getIdtfValue(ms_context.get(), type1,
																				 Keynodes::nrel_main_idtf);
										SC_LOG_INFO(strin1);
										string str1 = CommonUtils::getIdtfValue(ms_context.get(), study3,
																			   Keynodes::nrel_probability);
										SC_LOG_INFO(str1);
									}

								}*/
								/*
								for(int d=0; d<forms[a][b][c].size();d++){
									for(int e=0; e<forms[a][b][c][d].size();e++) {
										ScAddr node = forms[a][b][c][d][e];
										if (node.IsValid()) {
											string strtemp =
													"[" + to_string(a) + "] " + "[" + to_string(b) + "] " + "[" +
													to_string(c) + "] " + "[" + to_string(d) + "] " + "[" +
													to_string(e) + "]";
											SC_LOG_INFO(strtemp);
											ScAddr type;
											ScIterator3Ptr TypeIT = ms_context->Iterator3(ScType::Unknown,
																						  ScType::EdgeAccessConstPosPerm,
																						  node);
											while (TypeIT->Next()) {
												type = TypeIT->Get(0);
											}
											string strin = CommonUtils::getIdtfValue(ms_context.get(), type,
																					 Keynodes::nrel_main_idtf);
											SC_LOG_INFO(strin);
											string str = CommonUtils::getIdtfValue(ms_context.get(), node,
																				   Keynodes::nrel_probability);
											SC_LOG_INFO(str);

										}
										/*
										ScAddr node1 = study[a][b][c][d][e];
										if (node1.IsValid()) {
											string strtemp1 =
													"[" + to_string(a) + "] " + "[" + to_string(b) + "] " + "[" +
													to_string(c) + "] " + "[" + to_string(d) + "] " + "[" +
													to_string(e) + "]";
											SC_LOG_INFO(strtemp1);
											ScAddr type1;
											ScIterator3Ptr TypeIT = ms_context->Iterator3(ScType::Unknown,
																						  ScType::EdgeAccessConstPosPerm,
																						  node1);
											while (TypeIT->Next()) {
												type1 = TypeIT->Get(0);
											}
											string strin1 = CommonUtils::getIdtfValue(ms_context.get(), type1,
																					 Keynodes::nrel_main_idtf);
											SC_LOG_INFO(strin1);
											string str1 = CommonUtils::getIdtfValue(ms_context.get(), node1,
																				   Keynodes::nrel_probability);
											SC_LOG_INFO(str1);
										}*/
										//  }
										//}*/
										//}
										//}
										//}



						/*
											vector <ScAddr> artifacts;
											ScIterator3Ptr artIT = ms_context->Iterator3(spatials, ScType::EdgeAccessConstPosPerm,
											ScType::Unknown);
											while (artIT->Next()) {
												artifacts.push_back(artIT->Get(2));
											}
											vector <ScAddr> art_type;
											vector <vector <vector < vector < vector < ScAddr>>>>>first;
											vector <vector < vector < vector < ScAddr>>>>second;

											vector < vector < vector < ScAddr>>> artifacts_v;
											for (int j = 0; j < artifacts.size(); j++) {

												ScIterator3Ptr arttype = ms_context->Iterator3(ScType::Unknown,
																							   ScType::EdgeAccessConstPosPerm,
																							   artifacts[j]);
												while (arttype->Next()) {
													art_type.push_back(arttype->Get(0));
												}
											}

											for (int j = 0; j < artifacts.size(); j++) {
												vector <vector<ScAddr>> artifact;
												vector <ScAddr> a_type_v;
												a_type_v.push_back(artifacts[j]);
												artifact.push_back(a_type_v);
												//ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, art_type[j]);


												SC_LOG_INFO("/////")
												ScIterator5Ptr shapeIT = ms_context->Iterator5(artifacts[j], ScType::EdgeDCommonConst,
																							   ScType::Unknown,
																							   ScType::EdgeAccessConstPosPerm,
																							   Keynodes::nrel_shape_of_mass);
												vector <ScAddr> shape;
												while (shapeIT->Next()) {
													shape.push_back(shapeIT->Get(2));
												}


												vector <ScAddr> shape_type;
												for (int k = 0; k < shape.size(); k++) {
													ScIterator3Ptr shapeTypeIT = ms_context->Iterator3(ScType::Unknown,
																									   ScType::EdgeAccessConstPosPerm,
																									   shape[k]);
													while (shapeTypeIT->Next()) {
														shape_type.push_back(shapeTypeIT->Get(0));
													}
												}
												for (int k = 0; k < shape_type.size(); k++) {
													if (shape_type[k].IsValid()) {
														SC_LOG_INFO("shape");

														string shape_str = CommonUtils::getIdtfValue(ms_context.get(), shape_type[k],
																									 Keynodes::nrel_main_idtf);
														SC_LOG_INFO(shape_str);
													}
												}
												artifact.push_back(shape);

												//края

												ScIterator5Ptr margIT = ms_context->Iterator5(artifacts[j], ScType::EdgeDCommonConst,
																							  ScType::Unknown,
																							  ScType::EdgeAccessConstPosPerm,
																							  Keynodes::nrel_margins_of_mass);
												vector <ScAddr> marg;
												while (margIT->Next()) {
													marg.push_back(margIT->Get(2));
												}


												vector <ScAddr> marg_type;
												for (int k = 0; k < marg.size(); k++) {
													ScIterator3Ptr margTypeIT = ms_context->Iterator3(ScType::Unknown,
																									  ScType::EdgeAccessConstPosPerm,
																									  marg[k]);
													while (margTypeIT->Next()) {
														marg_type.push_back(margTypeIT->Get(0));
													}
												}
												for (int k = 0; k < marg_type.size(); k++) {
													if (marg_type[k].IsValid()) {
														SC_LOG_INFO("margins");
														string marg_str = CommonUtils::getIdtfValue(ms_context.get(), marg_type[k],
																									Keynodes::nrel_main_idtf);
														SC_LOG_INFO(marg_str)
													}
												}
												artifact.push_back(marg);
												//плотность

												ScIterator5Ptr denIT = ms_context->Iterator5(artifacts[j], ScType::EdgeDCommonConst,
																							 ScType::Unknown,
																							 ScType::EdgeAccessConstPosPerm,
																							 Keynodes::nrel_mass_density);
												vector <ScAddr> den;
												while (denIT->Next()) {
													den.push_back(denIT->Get(2));
												}


												vector <ScAddr> den_type;
												for (int k = 0; k < den.size(); k++) {
													ScIterator3Ptr denTypeIT = ms_context->Iterator3(ScType::Unknown,
																									 ScType::EdgeAccessConstPosPerm,
																									 den[k]);
													while (denTypeIT->Next()) {
														den_type.push_back(denTypeIT->Get(0));
													}
												}
												for (int k = 0; k < den_type.size(); k++) {
													if (den_type[k].IsValid()) {
														SC_LOG_INFO("density");
														string den_str = CommonUtils::getIdtfValue(ms_context.get(), den_type[k],
																								   Keynodes::nrel_main_idtf);
														SC_LOG_INFO(den_str)
													}
												}
												artifact.push_back(den);
												//размер

												ScIterator5Ptr sizeIT = ms_context->Iterator5(artifacts[j], ScType::EdgeDCommonConst,
																							  ScType::Unknown,
																							  ScType::EdgeAccessConstPosPerm,
																							  Keynodes::nrel_artifact_size);
												vector<ScAddr> size;
												while (sizeIT->Next()) {
													size.push_back(sizeIT->Get(2));
												}

												for(int k=0; k<size.size(); k++) {
													if (size[k].IsValid()) {
														SC_LOG_INFO("size");
														string size_str = CommonUtils::getIdtfValue(ms_context.get(), artifacts[j],
																									Keynodes::nrel_artifact_size);
														SC_LOG_INFO(size_str)
													}
												}
												artifact.push_back(size);


												//////////////////////////кальцинаты


												ScIterator5Ptr distIT = ms_context->Iterator5(artifacts[j], ScType::EdgeDCommonConst,
																							  ScType::Unknown,
																							  ScType::EdgeAccessConstPosPerm,
																							  Keynodes::nrel_calc_distribution);
												vector <ScAddr> dist;
												while (distIT->Next()) {
													dist.push_back(distIT->Get(2));
												}


												vector <ScAddr> dist_type;
												for (int k = 0; k < dist.size(); k++) {
													ScIterator3Ptr distTypeIT = ms_context->Iterator3(ScType::Unknown,
																									  ScType::EdgeAccessConstPosPerm,
																									  dist[k]);
													while (distTypeIT->Next()) {
														dist_type.push_back(distTypeIT->Get(0));
													}
												}

												for (int k = 0; k < dist_type.size(); k++) {
													if (dist_type[k].IsValid()) {
														SC_LOG_INFO("dist");
														string dist_str = CommonUtils::getIdtfValue(ms_context.get(), dist_type[k],
																									Keynodes::nrel_main_idtf);
														SC_LOG_INFO(dist_str)
													}
												}
												artifact.push_back(dist);

												artifacts_v.push_back(artifact);
											}

											second.push_back(artifacts_v);
											first.push_back(second);

						*/
						//}////////////////////////////////////////
		/*
							for(int a=0; a<forms.size(); a++){
								for(int b=0; b<forms[a].size();b++){
									for(int c=0; c<forms[a][b].size();c++){
										for(int d=0; d<forms[a][b][c].size();d++){
											for(int e=0; e<forms[a][b][c][d].size();e++){
												ScAddr node = forms[a][b][c][d][e];
												if (node.IsValid()){
													string strtemp="["+to_string(a)+"] "+"["+to_string(b)+"] "+"["+to_string(c)+"] "+"["+to_string(d)+"] "+"["+to_string(e)+"]";
													SC_LOG_INFO(strtemp);
													ScAddr type;
													ScIterator3Ptr TypeIT = ms_context->Iterator3(ScType::Unknown,
																									 ScType::EdgeAccessConstPosPerm,
																									 node);
													while (TypeIT->Next()) {
														type=TypeIT->Get(0);
													}
													string strin = CommonUtils::getIdtfValue(ms_context.get(), type, Keynodes::nrel_main_idtf);
													SC_LOG_INFO(strin);
													string str = CommonUtils::getIdtfValue(ms_context.get(), node, Keynodes::nrel_probability);
													SC_LOG_INFO(str);
												}
											}
										}
									}
								}
							}
		*/
                //ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, spatials);
		SC_LOG_INFO("----------counter end----------");
		AgentUtils::finishAgentWork(ms_context.get(), questionNode, answer);
		return SC_RESULT_OK;
	}
}
