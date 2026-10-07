#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_LEN 1024

int main(int argc, char *argv[])
{
	    if(argc != 2){
			        fprintf(stderr,"用法：%s input.txt\n",argv[0]);
					        return EXIT_FAILURE;
							    }

								    FILE *fp = fopen(argv[1],"r");
									    if(!fp){
											        perror("打开文件失败");
													        return EXIT_FAILURE;
															    }

																    char line[BUF_LEN];
																	    int count = 0;
																		    printf("===== Extract News Url & Title =====\n");

																			    while(fgets(line, BUF_LEN, fp) != NULL)
																					    {
																							        char *cur = line;
																									        //循环找 <a href="
																											        while( (cur = strstr(cur,"<a href=\"")) != NULL )
																														        {
																																	            cur += strlen("<a href=\"");
																																				            char *url_end = strstr(cur,"\"");
																																							            if(url_end == NULL) break;

																																										            char url[256]={0};
																																													            strncpy(url, cur, url_end - cur);

																																																            cur = url_end;
																																																			            cur = strstr(cur,">");
																																																						            if(cur == NULL) break;
																																																									            cur++;

																																																												            char *title_end = strstr(cur,"</a>");
																																																															            if(title_end == NULL) break;

																																																																		            char title[256]={0};
																																																																					            strncpy(title, cur, title_end - cur);

																																																																								            //去掉前后空格
																																																																											            char *p = title;
																																																																														            while(*p == ' ') p++;
																																																																																	            if(strlen(p) > 1)
																																																																																					            {
																																																																																									                count++;
																																																																																													                printf("[%03d] URL: %s\n",count,url);
																																																																																																	                printf("      TITLE: %s\n\n",p);
																																																																																																					            }
																																																																																																								            cur = title_end + strlen("</a>");
																																																																																																											        }
																																																																																																													    }
																																																																																																														    fclose(fp);

																																																																																																															    if(count == 0){
																																																																																																																	        printf("No news item matched!\n");
																																																																																																																			    }else{
																																																																																																																					        printf("Total extracted news items: %d\n",count);
																																																																																																																							    }
																																																																																																																								    return EXIT_SUCCESS;
}

